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

ctypedef struct darray:
    void *array
    size_t item_size
    unsigned int used_count
    unsigned int allocated_count

cdef int darray_init(darray *darray, size_t item_size) except -1:
    darray.array = NULL
    darray.item_size = item_size
    darray.used_count = 0
    darray.allocated_count = 8
    reallocate(&darray.array,
               darray.allocated_count * darray.item_size)
    return 0

cdef void *darray_add(darray *darray) except NULL:
    cdef void *result
    cdef unsigned int new_used_count, new_allocated_count

    new_used_count = darray.used_count + 1
    if new_used_count > darray.allocated_count:
        new_allocated_count = max(1, darray.allocated_count) * 2
        assert new_allocated_count >= new_used_count
        reallocate(&darray.array,
                   new_allocated_count * darray.item_size)
        darray.allocated_count = new_allocated_count

    result = &(<unsigned char *>darray.array)[darray.used_count * darray.item_size]
    darray.used_count = new_used_count
    return result

cdef void *darray_last(darray *darray) except NULL:
    return &(<unsigned char *>darray.array)[(darray.used_count - 1) * darray.item_size]

cdef void darray_fini(darray *darray):
    free(darray.array)
    darray.array = NULL
    darray.used_count = -1
    # Keep the item_size for debuggability

cdef int darray_fast_remove_last(darray *darray) except -1:
    cdef unsigned int new_used_count, new_allocated_count

    assert darray.used_count > 0
    new_used_count = darray.used_count - 1
    darray.used_count = new_used_count
    return 0

# TODO: remove_last (non-fast)
#     if darray.allocated_count>8 and new_used_count < darray.allocated_count/4:
#         new_allocated_count = darray.allocated_count/2
#         reallocate(&darray.array,
#                    new_allocated_count * darray.item_size)
#         darray.allocated_count = new_allocated_count
