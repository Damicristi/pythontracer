cdef extern from "errno.h":
    int errno

cdef extern from "sys/time.h":
    ctypedef long time_t
    ctypedef long suseconds_t
    struct timeval:
        time_t tv_sec
        suseconds_t tv_usec
    struct timezone:
        int tz_minuteswest
        int tz_dsttime

cdef extern from "time.h":
    int gettimeofday(timeval *tv, timezone *tz)

cdef extern from "sys/times.h":
    ctypedef int clock_t
    struct tms:
        clock_t tms_utime
        clock_t tms_stime
        clock_t tms_cutime
        clock_t tms_cstime
    clock_t times(tms *buf)

cdef extern from "sys/param.h":
    int HZ
