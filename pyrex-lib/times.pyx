# Written by Eyal Lotem <eyal.lotem+pt@gmail.com>
# Copyright (2007-2008)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from libc.errno cimport errno
from posix.resource cimport RUSAGE_SELF, rusage, getrusage
from posix.time cimport gettimeofday, timeval

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
