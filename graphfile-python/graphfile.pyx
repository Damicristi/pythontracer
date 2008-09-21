include "memory.pyx"
include "python.pyx"

class Error(Exception): pass

cdef class _Linkable:
    cdef graphfile_linkable_t linkable

cdef class Writer:
    cdef graphfile_writer_t writer
    cdef readonly object fileobj

    def __cinit__(self, fileobj):
        if 0 != graphfile_writer_init(&self.writer, file_from_obj(fileobj)):
            raise Error("graphfile_writer_init")
        self.fileobj = fileobj
    def __dealloc__(self):
        graphfile_writer_fini(&self.writer)

    def set_root(self, _Linkable root):
        if 0 != graphfile_writer_set_root(&self.writer, &root.linkable):
            raise Error("graphfile_writer_set_root")

    def write(self, data, linkables):
        cdef _Linkable result_linkable
        cdef char *buffer
        cdef Py_ssize_t buffer_length
        cdef graphfile_linkable_t *c_linkables
        cdef graphfile_size_t i
        cdef int result

        PyString_AsStringAndSize(data, &buffer, &buffer_length)
        c_linkables = <graphfile_linkable_t *>allocate(sizeof(graphfile_linkable_t) * len(linkables))
        try:
            for i, linkable in enumerate(linkables):
                c_linkables[i] = (<_Linkable>linkable).linkable
            result_linkable = _Linkable()
            result = graphfile_writer_write(&self.writer, buffer, buffer_length,
                                            c_linkables, len(linkables),
                                            &result_linkable.linkable)
            if result != 0:
                raise Error("graphfile_writer_write")
            return result_linkable
        finally:
            free(c_linkables)

cdef class Reader:
    cdef graphfile_reader_t reader
    cdef readonly _Linkable root
    cdef readonly object fileobj
    def __cinit__(self, fileobj):
        self.root = _Linkable()
        if 0 != graphfile_reader_init(&self.reader, file_from_obj(fileobj), &self.root.linkable):
            raise Error("graphfile_reader_init")
        self.fileobj = fileobj
    def __dealloc__(self):
        graphfile_reader_fini(&self.reader)
    def read(self, _Linkable linkable):
        cdef graphfile_size_t i
        cdef int result

        cdef char *result_buffer
        cdef graphfile_linkable_t *result_linkables

        cdef graphfile_size_t result_buffer_length, new_result_buffer_length
        cdef graphfile_size_t result_linkables_count, new_result_linkables_count
        result = graphfile_reader_read(
            &self.reader,
            &linkable.linkable,

            NULL, 0,
            &result_buffer_length,

            NULL, 0,
            &result_linkables_count)
        if result != 0:
            raise Error("graphfile_reader_read")

        result_buffer = <char *>allocate(result_buffer_length)
        try:
            result_linkables = <graphfile_linkable_t *>allocate(result_linkables_count * sizeof(graphfile_linkable_t))
            try:
                result = graphfile_reader_read(
                    &self.reader,
                    &linkable.linkable,

                    result_buffer, result_buffer_length,
                    &new_result_buffer_length,

                    result_linkables, result_linkables_count,
                    &new_result_linkables_count)
                if result != 0:
                    raise Error("graphfile_reader_read")
                if (new_result_buffer_length != result_buffer_length or
                    new_result_linkables_count != result_linkables_count):
                    raise Error("File has changed within a single read")
                data = PyString_FromStringAndSize(result_buffer, result_buffer_length)
                linkables = []
                for i from 0 <= i < result_linkables_count:
                    # NOTE: Overriding argument linkable
                    linkable = _Linkable()
                    linkable.linkable = result_linkables[i]
                    linkables.append(linkable)
                return data, linkables
            finally:
                free(result_linkables)
        finally:
            free(result_buffer)
