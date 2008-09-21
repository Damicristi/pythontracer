include "posix.pxd"
include "times.pyx"
include "memory.pyx"
include "python.pyx"
include "darray.pyx"
include "graphfile-python/graphfile.pxd"

ctypedef struct CodeObject:
    char filename[16]
    char name[16]

# This is the format that gets written directly to file:
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

cdef void call_invocation_init(CallInvocation *invocation,
                               object code_obj, int lineno,
                               double user_time,
                               double sys_time,
                               double real_time):
    cdef char *buf

    PyString_AsStringAndSize(code_obj.co_filename, &buf, NULL)
    strncpy(invocation.data.code_object.filename, buf,
            sizeof(invocation.data.code_object.filename))

    PyString_AsStringAndSize(code_obj.co_name, &buf, NULL)
    strncpy(invocation.data.code_object.name, buf,
            sizeof(invocation.data.code_object.name))

    invocation.data.lineno = lineno
    invocation.data.user_time = user_time
    invocation.data.sys_time = sys_time
    invocation.data.real_time = real_time
    darray_init(&invocation.children, sizeof(graphfile_linkable_t))

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef readonly object fileobj
    cdef graphfile_writer_t writer
    cdef darray stack
    cdef pid_t tracer_pid
    def __cinit__(self, fileobj):
        if 0 != graphfile_writer_init(&self.writer, file_from_obj(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
        self.tracer_pid = -1
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    cdef int _trace_event(self, object frame, int event, void *trace_arg) except -1:
        cdef double user_time, sys_time, real_time
        cdef CallInvocation *invocation
        cdef graphfile_linkable_t linkable

        if self.tracer_pid != getpid():
            # Ignore forked children events... Don't let them corrupt
            # our file.
            return 0
        if event != PyTrace_CALL and event != PyTrace_RETURN:
            return 0

        get_user_sys_times(&user_time, &sys_time)
        get_real_time(&real_time)

        if event == PyTrace_CALL:
            invocation = <CallInvocation *>darray_add(&self.stack)
            call_invocation_init(invocation, frame.f_code, frame.f_lineno, user_time, sys_time, real_time)
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
        self.tracer_pid = getpid()
        try:
            assert self.stack.used_count == 1, "The stack had: %d" % (self.stack.used_count,)
            PyEval_SetProfile(<Py_tracefunc>&callback, self)
            try:
                return func()
            finally:
                PyEval_SetProfile(NULL, None)
                assert self.stack.used_count == 1, "The stack had: %d" % (self.stack.used_count,)
                if self.tracer_pid == getpid():
                    # darray may have moved around due to re-allocations, re-take pointer:
                    invocation = <CallInvocation *>darray_last(&self.stack)
                    self._write(NULL, 0, &invocation.children, &root)
                    darray_remove_last(&self.stack)
                    if 0 != graphfile_writer_set_root(&self.writer, &root):
                        raise Error("graphfile_writer_set_root")
        finally:
            self.tracer_pid = -1
            darray_fini(&self.stack)

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg) except -1:
    tracer._trace_event(frame, event, trace_arg)
    return 0
