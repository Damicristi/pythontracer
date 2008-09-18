cdef extern from "stdio.h":
    ctypedef struct FILE

cdef extern from "sys/types.h":
    ctypedef unsigned long size_t
    ctypedef int pid_t

cdef extern from "unistd.h":
    pid_t getpid()
