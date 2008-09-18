from posix cimport size_t

ctypedef struct DArray:
    void *array
    size_t item_size
    unsigned int used_count
    unsigned int allocated_count

cdef void darray_init(DArray *darray, size_t item_size)
cdef int darray_add(DArray *darray, void *item) except -1
