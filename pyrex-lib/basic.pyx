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

from posix cimport FILE, fopen, fclose

cdef extern from "frameobject.h":
    ctypedef struct PyFrameObject:
        pass

cdef extern from "Python.h":
    object PyBytes_FromStringAndSize(char *, Py_ssize_t)
    int PyBytes_AsStringAndSize(object, char **s, Py_ssize_t *len) except -1
    char *PyUnicode_AsUTF8(object) except NULL
    char *PyUnicode_AsUTF8AndSize(object, Py_ssize_t *size) except NULL
    enum PyTraceEvent:
        PyTrace_CALL
        PyTrace_EXCEPTION
        PyTrace_LINE
        PyTrace_RETURN
        PyTrace_C_CALL
        PyTrace_C_EXCEPTION
        PyTrace_C_RETURN

    ctypedef int Py_tracefunc(object arg, PyFrameObject *frame, int what, object info) except -1
    void PyEval_SetProfile(Py_tracefunc *func, object arg)
    # PyEval_SetTrace is the same as PyEval_SetProfile, except it also
    # gets line number events
    void PyEval_SetTrace(Py_tracefunc *func, object arg)

class Error(Exception): pass

cdef FILE *fopen_str(object filepath, const char *mode) except NULL:
    cdef FILE *f = fopen(PyUnicode_AsUTF8(filepath), mode)
    if NULL == f:
        print("RAISING")
        raise Error("Invalid fileobj")
    print("Opened: " + filepath)
    return f
