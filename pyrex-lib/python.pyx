cdef FILE *file_from_obj(fileobj):
    cdef FILE *file
    file = PyFile_AsFile(fileobj)
    if NULL == file:
        raise Error("Invalid fileobj")
    return file
