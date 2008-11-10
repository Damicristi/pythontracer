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

from posix cimport FILE

cdef extern from "Python.h":
    object PyString_FromStringAndSize(char *, Py_ssize_t)
    int PyString_AsStringAndSize(object, char **s, Py_ssize_t *len) except -1
    enum PyTraceEvent:
        PyTrace_CALL
        PyTrace_EXCEPTION
        PyTrace_LINE
        PyTrace_RETURN
        PyTrace_C_CALL
        PyTrace_C_EXCEPTION
        PyTrace_C_RETURN

    FILE *PyFile_AsFile(fileobj)
    ctypedef void *Py_tracefunc
    void PyEval_SetProfile(Py_tracefunc func, object arg)
    # PyEval_SetTrace is the same as PyEval_SetProfile, except it also
    # gets line number events
    void PyEval_SetTrace(Py_tracefunc func, object arg)

cdef FILE *file_from_obj(fileobj) except NULL:
    cdef FILE *file
    file = PyFile_AsFile(fileobj)
    if NULL == file:
        raise Error("Invalid fileobj")
    return file
