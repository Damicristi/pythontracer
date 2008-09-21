cdef extern from "errno.h":
    int errno

cdef extern from "sys/types.h":
    ctypedef unsigned long size_t
    ctypedef int pid_t

cdef extern from "stdio.h":
    ctypedef struct FILE
    int fflush(FILE *stream)
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream)

cdef extern from "unistd.h":
    pid_t getpid()
