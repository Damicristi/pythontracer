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

cimport libc.stdio as stdio

cdef int safe_fflush(stdio.FILE *stream) except -1:
    if -1 == stdio.fflush(stream):
        raise OSError(stdio.errno, "fflush")
    return 0

cdef size_t safe_fread(void *ptr, size_t size, stdio.FILE *stream) except -1:
    cdef int rc
    rc = stdio.fread(ptr, 1, size, stream)
    if rc == -1:
        raise OSError(stdio.errno, "fread")
    return rc

cdef size_t safe_fwrite(void *ptr, size_t size, stdio.FILE *stream) except -1:
    cdef int rc
    rc = stdio.fwrite(ptr, 1, size, stream)
    if rc == -1:
        raise OSError(stdio.errno, "fwrite")
    return rc
