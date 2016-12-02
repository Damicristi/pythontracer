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

from libc.stdlib cimport malloc, realloc, free

cdef void *allocate(size_t size) except NULL:
    cdef void *ptr
    ptr = malloc(size)
    if ptr == NULL:
        raise MemoryError
    return ptr

cdef int reallocate(void **ptr, size_t size) except -1:
    cdef void *new_ptr
    if size == 0:
        free(ptr[0])
        ptr[0] = NULL
        return 0
    new_ptr = realloc(ptr[0], size)
    if new_ptr == NULL:
        raise MemoryError
    ptr[0] = new_ptr
    return 0
