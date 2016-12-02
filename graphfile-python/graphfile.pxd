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

from libc.stdio cimport FILE
from libc.stdint cimport uint32_t

cdef extern from "graphfile.h":
    ctypedef struct graphfile_writer_t:
        pass
    ctypedef struct graphfile_reader_t:
        pass
    ctypedef struct graphfile_node_t:
        pass
    int graphfile_writer_init(graphfile_writer_t *, FILE *file)
    int graphfile_writer_set_root(graphfile_writer_t *,
                                  graphfile_node_t *root)
    void graphfile_writer_fini(graphfile_writer_t *)

    int graphfile_writer_write(graphfile_writer_t *,
                               char *buffer, size_t buffer_length,
                               graphfile_node_t nodes[], uint32_t node_count,
                               graphfile_node_t *result_node)

    int graphfile_reader_init(graphfile_reader_t *, FILE *file,
                              graphfile_node_t *result_root)
    void graphfile_reader_fini(graphfile_reader_t *)

    int graphfile_reader_read(graphfile_reader_t *,
                              graphfile_node_t *node,

                              char *result_buffer, size_t max_buffer_length,
                              size_t *result_buffer_length,

                              graphfile_node_t result_nodes[], uint32_t max_node_count,
                              uint32_t *result_nodes_count)
