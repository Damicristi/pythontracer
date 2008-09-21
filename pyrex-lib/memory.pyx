from posix cimport size_t

cdef extern from "stdlib.h":
    void *malloc(size_t size)
    void *realloc(void *ptr, size_t size)
    void free(void *ptr)

cdef extern from "string.h":
    void *memcpy(void *dest, void *src, size_t n)
    void *memset(void *s, int c, size_t n)
    char *strcpy(char *dest, char *src)
    char *strncpy(char *dest, char *src, size_t n)

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
