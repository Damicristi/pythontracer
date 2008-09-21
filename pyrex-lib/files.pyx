cimport posix

cdef int safe_fflush(FILE *stream) except -1:
    if -1 == posix.fflush(stream):
        raise OSError(posix.errno, "fflush")
    return 0

cdef size_t safe_fread(void *ptr, size_t size, FILE *stream) except -1:
    cdef int rc
    rc = posix.fread(ptr, 1, size, stream)
    if rc == -1:
        raise OSError(posix.errno, "fread")
    return rc

cdef size_t safe_fwrite(void *ptr, size_t size, FILE *stream) except -1:
    cdef int rc
    rc = posix.fwrite(ptr, 1, size, stream)
    if rc == -1:
        raise OSError(posix.errno, "fwrite")
    return rc
