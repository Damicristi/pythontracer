cimport posix
cimport rotatingtree
include "times.pyx"
include "memory.pyx"
include "python.pyx"
include "darray.pyx"
include "files.pyx"
include "graphfile-python/graphfile.pxd"

import os
import sys

# This is the format that gets written directly to file:
ctypedef short code_index

ctypedef struct CodeObject:
    code_index index

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

cdef fwrite_string(object name, FILE *index_file):
    cdef char *name_buf
    cdef Py_ssize_t name_length
    cdef short short_name_length
    PyString_AsStringAndSize(name, &name_buf, &name_length)
    short_name_length = name_length

    # Don't let overlaps occur
    assert short_name_length == name_length

    safe_fwrite(&short_name_length, sizeof(short_name_length), index_file)
    safe_fwrite(name_buf, name_length, index_file)

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef readonly object fileobj
    cdef readonly object index_fileobj
    cdef rotatingtree.rotating_node_t *written_indexes
    cdef posix.FILE *index_file
    cdef graphfile_writer_t writer
    cdef darray stack
    cdef posix.pid_t tracer_pid
    cdef code_index next_code_index
    cdef object _prev_os_exit
    def __cinit__(self, fileobj, index_fileobj):
        self.next_code_index = 0
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
        invocation.data.code_object.index = self._index_of_code(code_obj)
        invocation.data.lineno = lineno
        invocation.data.user_time = user_time
        invocation.data.sys_time = sys_time
        invocation.data.real_time = real_time
        darray_init(&invocation.children, sizeof(graphfile_linkable_t))
        return 0

    cdef int _trace_event(self, object frame, int event, void *trace_arg) except -1:
        cdef double user_time, sys_time, real_time

        if self.tracer_pid != posix.getpid():
            # Ignore forked children events... Don't let them corrupt
            # our file.
            return 0
        if event != PyTrace_CALL and event != PyTrace_RETURN:
            return 0

        get_user_sys_times(&user_time, &sys_time)
        get_real_time(&real_time)

        if event == PyTrace_CALL:
            self._push_call(frame.f_code, frame.f_lineno, user_time, sys_time, real_time)
        else: # event == PyTrace_RETURN:   don't assert this for performance reasons
            self._pop_call(user_time, sys_time, real_time)
        return 0

    cdef int _push_call(self, object code_obj, int lineno, double user_time, double sys_time, double real_time) except -1:
        cdef CallInvocation *invocation

        invocation = <CallInvocation *>darray_add(&self.stack)
        self.call_invocation_init(invocation, code_obj, lineno, user_time, sys_time, real_time)
        return 0

    cdef int _pop_call(self, double user_time, double sys_time, double real_time) except -1:
        cdef CallInvocation *invocation
        cdef graphfile_linkable_t linkable
        cdef graphfile_linkable_t *new_child_ptr

        invocation = <CallInvocation *>darray_last(&self.stack)
        invocation.data.user_time = user_time - invocation.data.user_time
        invocation.data.sys_time = sys_time - invocation.data.sys_time
        invocation.data.real_time = real_time - invocation.data.real_time
        self._write(<char *>&invocation.data, sizeof(invocation.data),
                    &invocation.children, &linkable)
        darray_fini(&invocation.children)
        darray_fast_remove_last(&self.stack)
        # The parent invocation:
        invocation = <CallInvocation *>darray_last(&self.stack)
        new_child_ptr = <graphfile_linkable_t *>darray_add(&invocation.children)
        new_child_ptr[0] = linkable
        return 0

    cdef int _index_of_code(self, object code) except -1:
        cdef code_index index
        cdef object key

        # TODO: Is it ok to assume code objects keep around with their ID's?
        key = id(code)
        if key in self.written_indexes:
            return self.written_indexes[key]

        index = self.next_code_index

        # Prevent wraparounds:
        assert self.next_code_index != 0

        safe_fwrite(&index, sizeof(index), self.index_file)

        fwrite_string(code.co_filename, self.index_file)
        fwrite_string(code.co_name, self.index_file)

        self.written_indexes[key] = index
        self.next_code_index = index + 1

        return index

    cdef int _write(self, char *buffer, unsigned int buffer_length,
                    darray *children, graphfile_linkable_t *result) except -1:
        cdef int status
        status = graphfile_writer_write(&self.writer, buffer, buffer_length,
                                        <graphfile_linkable_t *>children.array, children.used_count, result)
        if status != 0:
            raise Error("graphfile_writer_write")
        return 0

    cdef _push_root(self):
        cdef CallInvocation *invocation
        invocation = <CallInvocation *>darray_add(&self.stack)
        call_invocation_empty(invocation)

    cdef _pop_root(self):
        cdef graphfile_linkable_t root
        cdef CallInvocation *invocation
        assert self.stack.used_count == 1
        # darray may have moved around due to re-allocations, re-take pointer:
        invocation = <CallInvocation *>darray_last(&self.stack)
        self._write(NULL, 0, &invocation.children, &root)
        darray_fast_remove_last(&self.stack)
        if 0 != graphfile_writer_set_root(&self.writer, &root):
            raise Error("graphfile_writer_set_root")

    cdef _pop_to_root(self):
        cdef double user_time, sys_time, real_time
        get_user_sys_times(&user_time, &sys_time)
        get_real_time(&real_time)
        while self.stack.used_count > 1:
            self._pop_call(user_time, sys_time, real_time)
        self._pop_root()

    def _wrap_os_exit(self, status):
        self._pop_to_root()
        self._prev_os_exit(status)

    def trace(self, func):
        assert self.tracer_pid == -1, "Cannot create a nested trace"
        darray_init(&self.stack, sizeof(CallInvocation))
        self._push_root()
        self.tracer_pid = posix.getpid()
        self.written_indexes = {}
        try:
            PyEval_SetProfile(<Py_tracefunc>&callback, self)
            self._prev_os_exit = os._exit
            os._exit = self._wrap_os_exit
            try:
                try:
                    try:
                        return func()
                    finally:
                        assert os._exit == self._wrap_os_exit
                        os._exit = self._prev_os_exit
                        PyEval_SetProfile(NULL, None)
                except:
                    if self.tracer_pid == posix.getpid():
                        exc_type, exc_value, exc_tb = sys.exc_info()
                        try:
                            self._pop_root()
                        except:
                            # Raise the original exception
                            raise exc_type, exc_value, exc_tb
                    raise
            finally:
                # Normal return (we already covered exceptional
                # return) requires finally, as we use "return" above
                if self.tracer_pid == posix.getpid():
                    self._pop_root()
        finally:
            self.written_indexes = None
            self.tracer_pid = -1
            darray_fini(&self.stack)

cdef int callback(Tracer tracer, object frame, int event, void *trace_arg) except -1:
    tracer._trace_event(frame, event, trace_arg)
    return 0
