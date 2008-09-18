cimport memory

cdef void darray_init(DArray *darray, size_t item_size):
    darray.array = NULL
    darray.item_size = item_size
    darray.used_count = darray.allocated_count = 0

cdef int darray_add(DArray *darray, void *item) except -1:
    cdef unsigned int new_used_count, new_allocated_count

    new_used_count = darray.used_count + 1
    if new_used_count > darray.allocated_count:
        new_allocated_count = darray.allocated_count * 2
        memory.reallocate(&darray.array,
                          new_allocated_count * darray.item_size)
        darray.allocated_count = new_allocated_count

    memory.memcpy(&(<unsigned char *>darray.array)[darray.used_count * darray.item_size],
                  item, darray.item_size)
    darray.used_count = new_used_count
