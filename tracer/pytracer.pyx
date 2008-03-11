from marshal import dumps

cdef extern from "sys/types.h":
    ctypedef unsigned long size_t
    ctypedef int pid_t

cdef extern from "errno.h":
    int errno
    
cdef extern from "sys/param.h":
    int HZ

cdef extern from "unistd.h":
    pid_t getpid()

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

cdef extern from "sys/times.h":
    ctypedef int clock_t
    struct tms:
        clock_t tms_utime
        clock_t tms_stime
        clock_t tms_cutime
        clock_t tms_cstime
    clock_t times(tms *buf)
               

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
    ctypedef unsigned long long graphfile_size_t
    ctypedef struct graphfile_writer_t:
        pass
    ctypedef struct graphfile_linkable_t:
        pass
    int graphfile_writer_init(graphfile_writer_t *, FILE *f)
    int graphfile_writer_set_root(graphfile_writer_t *,
                                  graphfile_linkable_t *root)
    void graphfile_writer_fini(graphfile_writer_t *)

    int graphfile_writer_write(graphfile_writer_t *,
                               char *buffer, graphfile_size_t buffer_length,
                               graphfile_linkable_t linkables[], graphfile_size_t linkable_count,
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
    cdef pid_t tracer_pid
    def __new__(self, fileobj):
        if 0 != graphfile_writer_init(&self.writer, get_file(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
        self.stack = None
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    cdef void _trace_event(self, object frame, int event, void *trace_arg):
        cdef tms times_result
        cdef clock_t times_return
        cdef double sys_time, user_time
        cdef unsigned long long real_time
        cdef timeval tv

        if self.tracer_pid != getpid():
            # Ignore forked children events... Don't let them corrupt
            # our file.
            return

        if event != PyTrace_CALL and event != PyTrace_RETURN:
            return
        if 0 != gettimeofday(&tv, NULL):
            raise Error("gettimeofday")
        real_time = (<unsigned long long>1000000 * tv.tv_sec) + <unsigned long long>tv.tv_usec

        errno = 0
        times_return = times(&times_result)
        if times_return == <clock_t>-1:
            raise OSError(errno, "times")
        user_time = <double>times_result.tms_utime / HZ
        sys_time = <double>times_result.tms_stime / HZ
        if event == PyTrace_CALL:
            self.stack.append(((frame.f_code, frame.f_lineno),
                               (user_time, sys_time, real_time), []))
        else:
            # Implies: PyTrace_RETURN:
            (code, lineno), (start_user_time, start_sys_time, start_real_time), children = self.stack.pop()
            child = self._write((((code.co_filename, code.co_name, lineno),
                                  (user_time - start_user_time,
                                   sys_time - start_sys_time,
                                   real_time - start_real_time)), children))
            parent_code, parent_times, parent_children = self.stack[-1]
            parent_children.append(child)

    cdef _encode(self, data):
        return dumps(data)

    cdef _write(self, node):
        data, linkables = node
        databuf = self._encode(data)
        cdef _Linkable result_linkable
        cdef char *buffer
        cdef Py_ssize_t buffer_length
        cdef graphfile_linkable_t *c_linkables
        cdef graphfile_size_t i
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
        assert self.stack is None, "Cannot create a nested trace"
        self.tracer_pid = getpid()
        self.stack = [(None, None, [])]
        PyEval_SetProfile(<Py_tracefunc>&callback, self)
        try:
            return func()
        finally:
            if self.tracer_pid == getpid():
                PyEval_SetProfile(NULL, None)
                code, times, children = self.stack.pop()
                assert not self.stack
                self.stack = None
                self.tracer_pid = -1
                root = self._write((None, children))
                if 0 != graphfile_writer_set_root(&self.writer, &root.linkable):
                    raise Error("graphfile_writer_set_root")

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg):
    tracer._trace_event(frame, event, trace_arg)
