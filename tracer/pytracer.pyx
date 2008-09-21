cimport posix
include "times.pyx"
include "memory.pyx"
include "python.pyx"
include "darray.pyx"
include "files.pyx"
include "graphfile-python/graphfile.pxd"

# This is the format that gets written directly to file:
ctypedef short string_index

ctypedef struct CodeObject:
    string_index filename_index
    string_index name_index

ctypedef struct InvocationData:
    CodeObject code_object
    int lineno
    double user_time, sys_time, real_time



ctypedef struct CallInvocation:
    InvocationData data
    # List of children
    darray children

cdef void call_invocation_empty(CallInvocation *invocation):
    memset(invocation, 0, sizeof(invocation[0]))
    darray_init(&invocation.children, sizeof(graphfile_linkable_t))

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef readonly object fileobj
    cdef readonly object index_fileobj
    cdef object written_indexes
    cdef posix.FILE *index_file
    cdef graphfile_writer_t writer
    cdef darray stack
    cdef posix.pid_t tracer_pid
    cdef string_index next_string_index
    def __cinit__(self, fileobj, index_fileobj):
        self.next_string_index = 0
        self.index_file = file_from_obj(index_fileobj)
        self.index_fileobj = index_fileobj

        if 0 != graphfile_writer_init(&self.writer, file_from_obj(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
        self.tracer_pid = -1
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    cdef int call_invocation_init(self,
                                  CallInvocation *invocation,
                                  object code_obj, int lineno,
                                  double user_time,
                                  double sys_time,
                                  double real_time) except -1:
        invocation.data.code_object.filename_index = self._index_of_name(code_obj.co_filename)
        invocation.data.code_object.name_index = self._index_of_name(code_obj.co_name)
        invocation.data.lineno = lineno
        invocation.data.user_time = user_time
        invocation.data.sys_time = sys_time
        invocation.data.real_time = real_time
        darray_init(&invocation.children, sizeof(graphfile_linkable_t))
        return 0

    cdef int _trace_event(self, object frame, int event, void *trace_arg) except -1:
        cdef double user_time, sys_time, real_time
        cdef CallInvocation *invocation
        cdef graphfile_linkable_t linkable

        if self.tracer_pid != posix.getpid():
            # Ignore forked children events... Don't let them corrupt
            # our file.
            return 0
        if event != PyTrace_CALL and event != PyTrace_RETURN:
            return 0

        get_user_sys_times(&user_time, &sys_time)
        get_real_time(&real_time)

        if event == PyTrace_CALL:
            invocation = <CallInvocation *>darray_add(&self.stack)
            self.call_invocation_init(invocation, frame.f_code, frame.f_lineno, user_time, sys_time, real_time)
        else: # event == PyTrace_RETURN:   don't assert this for performance reasons
            invocation = <CallInvocation *>darray_last(&self.stack)
            invocation.data.user_time = user_time - invocation.data.user_time
            invocation.data.sys_time = sys_time - invocation.data.sys_time
            invocation.data.real_time = real_time - invocation.data.real_time
            self._write(<char *>&invocation.data, sizeof(invocation.data),
                        &invocation.children, &linkable)
            darray_fini(&invocation.children)
            darray_remove_last(&self.stack)
            # The parent invocation:
            invocation = <CallInvocation *>darray_last(&self.stack)
            (<graphfile_linkable_t *>darray_add(&invocation.children))[0] = linkable
        return 0

    cdef int _index_of_name(self, object name) except -1:
        cdef char *name_buf
        cdef Py_ssize_t name_length
        cdef short short_name_length
        cdef string_index index
        if name in self.written_indexes:
            return self.written_indexes[name]
        PyString_AsStringAndSize(name, &name_buf, &name_length)
        short_name_length = name_length
        # Prevent wraparounds:
        assert short_name_length == name_length
        index = self.next_string_index
        safe_fwrite(&index, sizeof(index), self.index_file)
        safe_fwrite(&short_name_length, sizeof(short_name_length), self.index_file)
        safe_fwrite(name_buf, name_length, self.index_file)
        safe_fflush(self.index_file)
        self.written_indexes[name] = index
        self.next_string_index = index + 1
        # Don't let overlaps occur
        assert self.next_string_index != 0
        return index

    cdef int _write(self, char *buffer, unsigned int buffer_length,
                    darray *children, graphfile_linkable_t *result) except -1:
        cdef int status
        status = graphfile_writer_write(&self.writer, buffer, buffer_length,
                                        <graphfile_linkable_t *>children.array, children.used_count, result)
        if status != 0:
            raise Error("graphfile_writer_write")
        return 0

    def trace(self, func):
        cdef graphfile_linkable_t root
        cdef CallInvocation *invocation

        assert self.tracer_pid == -1, "Cannot create a nested trace"
        darray_init(&self.stack, sizeof(CallInvocation))
        invocation = <CallInvocation *>darray_add(&self.stack)
        call_invocation_empty(invocation)
        self.tracer_pid = posix.getpid()
        self.written_indexes = {}
        try:
            PyEval_SetProfile(<Py_tracefunc>&callback, self)
            try:
                return func()
            finally:
                PyEval_SetProfile(NULL, None)
                if self.tracer_pid == posix.getpid():
                    # darray may have moved around due to re-allocations, re-take pointer:
                    invocation = <CallInvocation *>darray_last(&self.stack)
                    self._write(NULL, 0, &invocation.children, &root)
                    darray_remove_last(&self.stack)
                    if 0 != graphfile_writer_set_root(&self.writer, &root):
                        raise Error("graphfile_writer_set_root")
        finally:
            self.written_indexes = None
            self.tracer_pid = -1
            darray_fini(&self.stack)
        assert self.stack.used_count == 0

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg) except -1:
    tracer._trace_event(frame, event, trace_arg)
    return 0
