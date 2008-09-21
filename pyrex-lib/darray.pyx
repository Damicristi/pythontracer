from posix cimport size_t

ctypedef struct darray:
    void *array
    size_t item_size
    unsigned int used_count
    unsigned int allocated_count

cdef void darray_init(darray *darray, size_t item_size):
    darray.array = NULL
    darray.item_size = item_size
    darray.used_count = darray.allocated_count = 0

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

cdef int darray_remove_last(darray *darray) except -1:
    cdef unsigned int new_used_count, new_allocated_count

    assert darray.used_count > 0
    new_used_count = darray.used_count - 1
    if new_used_count < darray.allocated_count/4:
        new_allocated_count = darray.allocated_count/4
        reallocate(&darray.array,
                   new_allocated_count * darray.item_size)
        darray.allocated_count = new_allocated_count
    darray.used_count = new_used_count
    return 0
