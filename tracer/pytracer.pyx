# Written by Eyal Lotem <eyal.lotem+pt@gmail.com>
# Copyright (2007-2008)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

cimport libc.stdio as stdio
cimport posix.unistd as unistd
cimport cpython.unicode as uni
cimport rotatingtree
from libc.string cimport memset
include "times.pyx"
include "memory.pyx"
include "pystate.pyx"
include "darray.pyx"
include "files.pyx"
include "graphfile.pxd"

import os
import sys

# This is the format that gets written directly to file:
ctypedef short CodeIndex

ctypedef struct CodeIndexEntry:
    rotatingtree.rotating_node_t header
    CodeIndex code_index

ctypedef struct InvocationData:
    CodeIndex index
    int lineno
    double user_time, sys_time, real_time

ctypedef struct CallInvocation:
    InvocationData data
    # List of children
    darray children

cdef void call_invocation_empty(CallInvocation *invocation):
    memset(invocation, 0, sizeof(invocation[0]))
    darray_init(&invocation.children, sizeof(graphfile_linkable_t))

cdef fwrite_with_len(s, FILE *index_file):
    cdef bytes buf
    if type(s) is unicode:
        buf = uni.PyUnicode_AsUTF8String(s)
        fwrite_bytes_with_len(buf, index_file)
    elif isinstance(s, bytes):
        fwrite_bytes_with_len(s, index_file)
    else:
        raise TypeError("fwrite_with_len called with non-string")

cdef fwrite_bytes_with_len(bytes buf, FILE *index_file):
    cdef short short_length = len(buf)
    assert short_length == len(buf)
    safe_fwrite(&short_length, sizeof(short_length), index_file)
    safe_fwrite(<char *>buf, short_length, index_file)

cdef int freeEntry(rotatingtree.rotating_node_t *header, void *arg):
    free(header)
    return 0

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Tracer:
    cdef rotatingtree.rotating_node_t *written_indexes
    cdef stdio.FILE *index_file
    cdef stdio.FILE *graph_file
    cdef char graphfile_inited
    cdef graphfile_writer_t writer
    cdef darray stack
    cdef unistd.pid_t tracer_pid
    cdef CodeIndex next_code_index
    cdef object _prev_os_exit
    def __cinit__(self, unicode filepath, unicode index_filepath):
        self.next_code_index = 0
        self.graphfile_inited = 0
        self.index_file = self.graph_file = NULL
        self.index_file = stdio.fopen(uni.PyUnicode_AsUTF8String(index_filepath), "wb")
        self.graph_file = stdio.fopen(uni.PyUnicode_AsUTF8String(filepath), "wb")
        if 0 != graphfile_writer_init(&self.writer, self.graph_file):
            raise Error("graphfile_writer_init")
        self.graphfile_inited = 1
        self.tracer_pid = -1
    def __dealloc__(self):
        if self.graphfile_inited: graphfile_writer_fini(&self.writer)
        if self.graph_file: stdio.fclose(self.graph_file)
        if self.index_file: stdio.fclose(self.index_file)

    cdef int call_invocation_init(self,
                                  CallInvocation *invocation,
                                  object code_obj, int lineno,
                                  double user_time,
                                  double sys_time,
                                  double real_time) except -1:
        invocation.data.index = self._index_of_code(code_obj)
        invocation.data.lineno = lineno
        invocation.data.user_time = user_time
        invocation.data.sys_time = sys_time
        invocation.data.real_time = real_time
        darray_init(&invocation.children, sizeof(graphfile_linkable_t))
        return 0

    cdef int _trace_event(self, PyFrameObject *frameobj, int event, object trace_arg) except -1:
        frame = <object>frameobj
        cdef double user_time, sys_time, real_time

        if self.tracer_pid != unistd.getpid():
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
        cdef unsigned long key
        cdef CodeIndexEntry *node

        # TODO: Is it ok to assume code objects keep around with their ID's?
        key = id(code)
        node = <CodeIndexEntry *>rotatingtree.RotatingTree_Get(&self.written_indexes, <void *>key)
        if node != NULL:
            return node.code_index

        node = <CodeIndexEntry *>malloc(sizeof(CodeIndexEntry))
        node.header.key = <void *>key
        node.code_index = self.next_code_index

        # Prevent wraparounds:
        assert self.next_code_index != 0

        safe_fwrite(&node.code_index, sizeof(node.code_index), self.index_file)

        fwrite_with_len(code.co_filename, self.index_file)
        fwrite_with_len(code.co_name, self.index_file)

        rotatingtree.RotatingTree_Add(&self.written_indexes, &node.header)
        self.next_code_index = node.code_index + 1
        return node.code_index

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
        self.tracer_pid = unistd.getpid()
        self.written_indexes = rotatingtree.EMPTY_ROTATING_TREE
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
                    if self.tracer_pid == unistd.getpid():
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
                if self.tracer_pid == unistd.getpid():
                    self._pop_root()
        finally:
            rotatingtree.RotatingTree_Enum(self.written_indexes, &freeEntry, NULL)
            self.written_indexes = NULL
            self.tracer_pid = -1
            darray_fini(&self.stack)

cdef int callback(object tracerobj, PyFrameObject *frame, int event, object trace_arg) except -1:
    cdef Tracer tracer = tracerobj
    tracer._trace_event(frame, event, trace_arg)
    return 0
