cdef void *allocate(size_t size) except NULL:
    cdef void *ptr
    ptr = malloc(size)
    if ptr == NULL:
        raise MemoryError
    return ptr

cdef int reallocate(void **ptr, size_t size) except -1:
    cdef void *new_ptr
    new_ptr = realloc(ptr[0], size)
    if new_ptr == NULL:
        raise MemoryError
    ptr[0] = new_ptr
    return 0

