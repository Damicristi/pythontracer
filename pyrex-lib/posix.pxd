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

cdef extern from "errno.h":
    int errno

cdef extern from "sys/types.h":
    ctypedef unsigned long size_t
    ctypedef int pid_t

cdef extern from "stdio.h":
    ctypedef struct FILE
    int fflush(FILE *stream)
    FILE *fopen(const char *path, const char *mode)
    int fclose(FILE *stream)
    size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream)
    size_t fwrite(void *ptr, size_t size, size_t nmemb, FILE *stream)

cdef extern from "unistd.h":
    pid_t getpid()
