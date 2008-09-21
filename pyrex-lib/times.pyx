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

cdef int get_user_sys_times(double *user_time, double *sys_time) except -1:
    cdef clock_t times_return
    cdef tms times_result

    # Get user/sys times
    errno = 0
    times_return = times(&times_result)
    if times_return == <clock_t>-1:
        raise OSError(errno, "times")
    user_time[0] = <double>times_result.tms_utime / HZ
    sys_time[0] = <double>times_result.tms_stime / HZ
    return 0

cdef int get_real_time(double *real_time) except -1:
    cdef timeval tv

    # Get real time
    if 0 != gettimeofday(&tv, NULL):
        raise Error("gettimeofday")
    real_time[0] = (<double>1000000 * tv.tv_sec) + <double>tv.tv_usec
    return 0
