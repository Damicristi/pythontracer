# TODO: Use a dynamic vector
MAX_RECURSION_DEPTH = 1000

cimport memory

ctypedef struct CodeObject:
    char *filename
    char *name

ctypedef struct CallInvocation:
    CodeObject code_object
    int lineno
    double user_time, sys_time, real_time
    # List of children
    graphfile_linkable_t *children

cdef void call_invocation_init(CallInvocation *invocation,
                               object code_obj, int lineno,
                               double user_time,
                               double sys_time,
                               double real_time):
    PyString_AsStringAndSize(code_obj.co_filename, &invocation->code_object.filename, NULL)
    PyString_AsStringAndSize(code_obj.co_name, &invocation->code_object.name, NULL)
    invocation.lineno = lineno
    invocation.user_time = user_time
    invocation.sys_time = sys_time
    invocation.real_time = real_time
    invocation.children = NULL

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef graphfile_writer_t writer
    cdef readonly object fileobj
    cdef CallInvocation stack[MAX_RECURSION_DEPTH]
    cdef unsigned int current_depth
    cdef pid_t tracer_pid
    def __new__(self, fileobj):
        if 0 != graphfile_writer_init(&self.writer, file_from_obj(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
        self.current_depth = 0
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    cdef void _trace_event(self, object frame, int event, void *trace_arg):
        cdef tms times_result
        cdef clock_t times_return
        cdef double user_time, sys_time, real_time
        cdef timeval tv

        if self.tracer_pid != getpid():
            # Ignore forked children events... Don't let them corrupt
            # our file.
            return

        if event != PyTrace_CALL and event != PyTrace_RETURN:
            return

        # Get user/sys times
        errno = 0
        times_return = times(&times_result)
        if times_return == <clock_t>-1:
            raise OSError(errno, "times")
        user_time = <double>times_result.tms_utime / HZ
        sys_time = <double>times_result.tms_stime / HZ

        # Get real time
        if 0 != gettimeofday(&tv, NULL):
            raise Error("gettimeofday")
        real_time = (<double>1000000 * tv.tv_sec) + <double>tv.tv_usec

        if event == PyTrace_CALL:
            cdef CallInvocation invocation
            call_invocation_init(&self.stack[self.current_depth], frame.f_code, frame.f_lineno, user_time, sys_time, real_time)
            self.current_depth += 1
        else:
            # Implies: PyTrace_RETURN:
            (code, lineno), (start_user_time, start_sys_time, start_real_time), children = self.stack.pop()
            child = self._write((((code.co_filename, code.co_name, lineno),
                                  # While each of these is an unsigned long long, the subtraction should really not yield times that are 
                                  (<double>user_time - start_user_time,
                                   <double>sys_time - start_sys_time,
                                   real_time - start_real_time)), children))
            parent_code, parent_times, parent_children = self.stack[-1]
            parent_children.append(child)

    cdef _Linkable _write(self, code_object,
                          int lineno,
                          unsigned long user_time,
                          unsigned long sys_time, real_time, ):
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
        PyEval_SetProfile(<Py_tracefunc>&callback, self)
        try:
            return func()
        finally:
            if self.tracer_pid == getpid():
                PyEval_SetProfile(NULL, None)
                code, times, children = self.stack.pop()
                assert not self.stack
                self.tracer_pid = -1
                root = self._write((None, children))
                if 0 != graphfile_writer_set_root(&self.writer, &root.linkable):
                    raise Error("graphfile_writer_set_root")

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg):
    tracer._trace_event(frame, event, trace_arg)
