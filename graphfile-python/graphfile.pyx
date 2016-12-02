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
cimport cpython.unicode as uni
include "memory.pyx"
include "pystate.pyx"

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_node_t node

cdef class Writer:
    cdef graphfile_writer_t writer
    cdef FILE *outfile

    def __cinit__(self, unicode filepath):
        self.outfile = stdio.fopen(uni.PyUnicode_AsUTF8String(filepath), "wb")
        if 0 != graphfile_writer_init(&self.writer, self.outfile):
            self._close_file()
            raise Error("graphfile_writer_init")
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)
        self._close_file()

    def _close_file(self):
        stdio.fclose(self.outfile)
        self.outfile = NULL

    def set_root(self, _Linkable root):
        if 0 != graphfile_writer_set_root(&self.writer, &root.node):
            raise Error("graphfile_writer_set_root")

    def write(self, bytes data, nodes):
        cdef _Linkable result_node
        cdef graphfile_node_t *c_nodes
        cdef int result
        cdef uint32_t i

        c_nodes = <graphfile_node_t *>allocate(sizeof(graphfile_node_t) * len(nodes))
        try:
            for i, node in enumerate(nodes):
                c_nodes[i] = (<_Linkable>node).node
            result_node = _Linkable()
            result = graphfile_writer_write(&self.writer, data, len(data),
                                            c_nodes, len(nodes),
                                            &result_node.node)
            if result != 0:
                raise Error("graphfile_writer_write")
            return result_node
        finally:
            free(c_nodes)

cdef class Reader:
    cdef graphfile_reader_t reader
    cdef readonly _Linkable root
    cdef readonly object filepath
    def __cinit__(self, filepath):
        self.root = _Linkable()
        if 0 != graphfile_reader_init(&self.reader, stdio.fopen(uni.PyUnicode_AsUTF8String(filepath), "rb"), &self.root.node):
            raise Error("graphfile_reader_init")
        self.filepath = filepath
    def __dealloc__(self):
        graphfile_reader_fini(&self.reader)
    def read(self, _Linkable node):
        cdef int result

        cdef char *result_buffer
        cdef graphfile_node_t *result_nodes

        cdef size_t result_buffer_length, new_result_buffer_length
        cdef uint32_t result_nodes_count, new_result_nodes_count
        cdef uint32_t i
        result = graphfile_reader_read(
            &self.reader,
            &node.node,

            NULL, 0,
            &result_buffer_length,

            NULL, 0,
            &result_nodes_count)
        if result != 0:
            raise Error("graphfile_reader_read")

        result_buffer = <char *>allocate(result_buffer_length)
        try:
            result_nodes = <graphfile_node_t *>allocate(result_nodes_count * sizeof(graphfile_node_t))
            try:
                result = graphfile_reader_read(
                    &self.reader,
                    &node.node,

                    result_buffer, result_buffer_length,
                    &new_result_buffer_length,

                    result_nodes, result_nodes_count,
                    &new_result_nodes_count)
                if result != 0:
                    raise Error("graphfile_reader_read")
                if (new_result_buffer_length != result_buffer_length or
                    new_result_nodes_count != result_nodes_count):
                    raise Error("File has changed within a single read")
                data = result_buffer[:result_buffer_length]
                nodes = []
                for i from 0 <= i < result_nodes_count:
                    # NOTE: Overriding argument node
                    node = _Linkable()
                    node.node = result_nodes[i]
                    nodes.append(node)
                return data, nodes
            finally:
                free(result_nodes)
        finally:
            free(result_buffer)
