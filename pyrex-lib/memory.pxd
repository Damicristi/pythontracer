from posix cimport size_t

cdef extern from "stdlib.h":
    void *malloc(size_t size)
    void *realloc(void *ptr, size_t size)
    void free(void *ptr)

cdef extern from "string.h":
    void *memcpy(void *dest, void *src, size_t n)

cdef void *allocate(size_t size) except NULL
cdef int reallocate(void **ptr, size_t size) except -1
