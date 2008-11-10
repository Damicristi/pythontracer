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
