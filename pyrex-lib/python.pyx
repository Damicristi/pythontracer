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
