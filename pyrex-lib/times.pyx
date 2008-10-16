from posix cimport errno

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

cdef extern from "sys/resource.h":
    struct rusage:
        timeval ru_utime
        timeval ru_stime
    int RUSAGE_SELF
    int getrusage(int who, rusage *usage)

cdef extern from "sys/param.h":
    int HZ

cdef double double_of_tv(timeval *tv):
    return (<double>1000000 * tv.tv_sec) + <double>tv.tv_usec

cdef int get_user_sys_times(double *user_time, double *sys_time) except -1:
    cdef int getrusage_return
    cdef rusage getrusage_result

    # Get user/sys times
    errno = 0
    getrusage_return = getrusage(RUSAGE_SELF, &getrusage_result)
    if getrusage_return == -1:
        raise OSError(errno, "getrusage")
    user_time[0] = double_of_tv(&getrusage_result.ru_utime)
    sys_time[0] = double_of_tv(&getrusage_result.ru_stime)
    return 0

cdef int get_real_time(double *real_time) except -1:
    cdef timeval tv

    # Get real time
    if 0 != gettimeofday(&tv, NULL):
        raise Error("gettimeofday")
    real_time[0] = double_of_tv(&tv)
    return 0
