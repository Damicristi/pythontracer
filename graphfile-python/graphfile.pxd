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

from posix cimport FILE

cdef extern from "graphfile.h":
    ctypedef unsigned long long graphfile_size_t
    ctypedef struct graphfile_writer_t:
        pass
    ctypedef struct graphfile_reader_t:
        pass
    ctypedef struct graphfile_linkable_t:
        pass
    int graphfile_writer_init(graphfile_writer_t *, FILE *file)
    int graphfile_writer_set_root(graphfile_writer_t *,
                                  graphfile_linkable_t *root)
    void graphfile_writer_fini(graphfile_writer_t *)

    int graphfile_writer_write(graphfile_writer_t *,
                               char *buffer, graphfile_size_t buffer_length,
                               graphfile_linkable_t linkables[], graphfile_size_t linkable_count,
                               graphfile_linkable_t *result_linkable)

    int graphfile_reader_init(graphfile_reader_t *, FILE *file,
                              graphfile_linkable_t *result_root)
    void graphfile_reader_fini(graphfile_reader_t *)

    int graphfile_reader_read(graphfile_reader_t *,
                              graphfile_linkable_t *node,

                              char *result_buffer, graphfile_size_t max_buffer_length,
                              graphfile_size_t *result_buffer_length,

                              graphfile_linkable_t result_linkables[], graphfile_size_t max_linkable_count,
                              graphfile_size_t *result_linkables_count)
