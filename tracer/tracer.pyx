from marshal import dumps

cdef extern from "sys/types.h":
    ctypedef unsigned long size_t

cdef extern from "sys/time.h":
    ctypedef long time_t
    ctypedef long suseconds_t
    struct timeval:
        time_t tv_sec
        suseconds_t tv_usec
    struct timezone:
        int tz_minuteswest
        int tz_dsttime

cdef extern from "time.h":
    int gettimeofday(timeval *tv, timezone *tz)

cdef extern from "stdlib.h":
    void *malloc(size_t size)
    void free(void *ptr)

cdef extern from "stdio.h":
    ctypedef struct FILE

cdef extern from "Python.h":
    ctypedef unsigned long Py_ssize_t
    int PyString_AsStringAndSize(object, char **s, Py_ssize_t *len) except -1
    enum PyTraceEvent:
        PyTrace_CALL
        PyTrace_EXCEPTION
        PyTrace_LINE
        PyTrace_RETURN
        PyTrace_C_CALL
        PyTrace_C_EXCEPTION
        PyTrace_C_RETURN

    FILE *PyFile_AsFile(fileobj)
    ctypedef void *Py_tracefunc
    void PyEval_SetProfile(Py_tracefunc func, object arg)
    # PyEval_SetTrace is the same as PyEval_SetProfile, except it also
    # gets line number events
    void PyEval_SetTrace(Py_tracefunc func, object arg)

cdef extern from "../graphfile/graphfile.h":
    ctypedef struct graphfile_writer_t:
        pass
    ctypedef struct graphfile_linkable_t:
        pass
    int graphfile_writer_init(graphfile_writer_t *, FILE *f)
    int graphfile_writer_set_root(graphfile_writer_t *,
                                  graphfile_linkable_t *root)
    void graphfile_writer_fini(graphfile_writer_t *)

    int graphfile_writer_write(graphfile_writer_t *,
                               char *buffer, size_t buffer_length,
                               graphfile_linkable_t linkables[], size_t linkable_count,
                               graphfile_linkable_t *result_linkable)

cdef void *allocate(int size):
    cdef void *ptr
    ptr = malloc(size)
    if ptr == NULL:
        raise MemoryError
    return ptr

class Error(Exception): pass

cdef FILE *get_file(fileobj):
    cdef FILE *file
    file = PyFile_AsFile(fileobj)
    if NULL == file:
        raise Error("Invalid fileobj")
    return file

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef graphfile_writer_t writer
    cdef readonly object fileobj
    cdef object stack
    def __new__(self, fileobj):
        if 0 != graphfile_writer_init(&self.writer, get_file(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    cdef void _trace_event(self, object frame, int event, void *trace_arg):
        cdef timeval tv
        if 0 != gettimeofday(&tv, NULL):
            raise Error("gettimeofday")
        cur_time = (<unsigned long long>1000000 * tv.tv_sec) + <unsigned long long>tv.tv_usec
        if event == PyTrace_CALL:
            self.stack.append((frame.f_code, cur_time, []))
        elif event == PyTrace_RETURN:
            code, start_time, children = self.stack.pop()
            child = self._write((((code.co_filename, code.co_name), (0, cur_time - start_time)), children))
            self.stack[-1][-1].append(child)

    cdef _encode(self, data):
        return dumps(data)

    cdef _write(self, node):
        data, linkables = node
        databuf = self._encode(data)
        cdef _Linkable result_linkable
        cdef char *buffer
        cdef Py_ssize_t buffer_length
        cdef graphfile_linkable_t *c_linkables
        cdef size_t i
        cdef int result
        
        PyString_AsStringAndSize(databuf, &buffer, &buffer_length)
        c_linkables = <graphfile_linkable_t *>allocate(sizeof(graphfile_linkable_t) * len(linkables))
        try:
            for i, linkable in enumerate(linkables):
                c_linkables[i] = (<_Linkable>linkable).linkable
            result_linkable = _Linkable()
            result = graphfile_writer_write(&self.writer, buffer, buffer_length,
                                            c_linkables, len(linkables),
                                            &result_linkable.linkable)
            if result != 0:
                raise Error("graphfile_writer_write")
            return result_linkable
        finally:
            free(c_linkables)

    def trace(self, func):
        cdef _Linkable root
        self.stack = [((('', ''), (0, 0)), [])]
        PyEval_SetProfile(<Py_tracefunc>&callback, self)
        try:
            return func()
        finally:
            PyEval_SetProfile(NULL, None)
            root = self._write(self.stack.pop())
            assert not self.stack
            if 0 != graphfile_writer_set_root(&self.writer, &root.linkable):
                raise Error("graphfile_writer_set_root")

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg):
    tracer._trace_event(frame, event, trace_arg)
