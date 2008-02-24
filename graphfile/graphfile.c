#include "graphfile.h"

#include <sys/types.h>
#include <unistd.h>

static int writen(int fd, const void *buffer, size_t buffer_size)
{
    /* TODO: Really writen here... */
    if(buffer_size != write(fd, buffer, buffer_size)) {
        return -1;
    }
    return 0;
}

static int readn(int fd, void *buffer, size_t buffer_size)
{
    /* TODO: Really readn here... */
    if(buffer_size != read(fd, buffer, buffer_size)) {
        return -1;
    }
    return 0;
}

static int seek(int fd, off_t offset) {
    if(offset != lseek(fd, offset, SEEK_SET)) {
        return -1;
    }
    return 0;
}

int graphfile_writer_init(graphfile_writer_t *graphfile_writer, int fd)
{
    off_t offset;
    graphfile_writer->fd = fd;
    offset = lseek(fd, 0, SEEK_END);
    if(offset == (off_t)-1) {
        /* A seekable file must be used */
        return -1;
    }
    if(offset > 0) {
        /* An empty file must be used */
        return -1;
    }
    if(0 != ftruncate(fd, sizeof(graphfile_linkable_t))) {
        /* A writable file must be used */
        return -1;
    }
    offset = lseek(fd, 0, SEEK_END);
    if(offset == (off_t)-1) {
        return -1;
    }
    return 0;
}

int graphfile_writer_set_root(graphfile_writer_t *graphfile_writer,
                              graphfile_linkable_t *root)
{
    off_t offset;
    int fd = graphfile_writer->fd;
    if(0 != seek(fd, 0)) {
        return -1;
    }
    if(0 != writen(fd, root, sizeof *root)) {
        return -1;
    }
    offset = lseek(fd, 0, SEEK_END);
    if(offset == (off_t)-1) {
        return -1;
    }
    return 0;
}

void graphfile_writer_fini(graphfile_writer_t *graphfile_writer)
{
    /* Not much to do here */
}

int graphfile_writer_write(graphfile_writer_t *graphfile_writer,
                           char *buffer, size_t buffer_length,
                           graphfile_linkable_t linkables[], size_t linkable_count,
                           graphfile_linkable_t *result_linkable)
{
    int fd = graphfile_writer->fd;
    off_t offset;
    offset = lseek(fd, 0, SEEK_CUR);
    if(offset == (off_t)-1) {
        return -1;
    }
    if((0 != writen(fd, &buffer_length, sizeof buffer_length)) ||
       (0 != writen(fd, buffer, buffer_length)) ||
       (0 != writen(fd, &linkable_count, sizeof linkable_count)) ||
       (0 != writen(fd, linkables, (sizeof linkables[0])*linkable_count)))
    {
        return -1;
    }
    result_linkable->offset = offset;
    return 0;
}


int graphfile_reader_init(graphfile_reader_t *graphfile_reader, int fd,
                          graphfile_linkable_t *result_root)
{
    graphfile_reader->fd = fd;
    if(0 != seek(fd, 0)) {
        /* A seekable file must be used */
        return -1;
    }
    if(0 != readn(fd, result_root, sizeof *result_root)) {
        /* A readable, coherent file must be used, so it must have a
         * readable root. */
        return -1;
    }
    return 0;
}

void graphfile_reader_fini(graphfile_reader_t *graphfile_reader)
{
    /* Nothing to do here */
}

#define UNSAFE_MIN(a, b)	(((a) <= (b)) ? (a) : (b))

int graphfile_reader_read(graphfile_reader_t *graphfile_reader,
                          graphfile_linkable_t *node,

                          char *result_buffer, size_t max_buffer_length,
                          size_t *result_buffer_length,
                          
                          graphfile_linkable_t result_linkables[], size_t max_linkable_count,
                          size_t *result_linkables_count)
{
    int fd = graphfile_reader->fd;
    if(0 != seek(fd, node->offset)) {
        return -1;
    }
    if((0 != readn(fd, result_buffer_length, sizeof *result_buffer_length)) ||
       (0 != readn(fd, result_buffer, UNSAFE_MIN(max_buffer_length, *result_buffer_length))))
    {
        return -1;
    }
    if((0 != seek(fd, node->offset + (sizeof *result_buffer_length) + *result_buffer_length)) ||
       (0 != readn(fd, result_linkables_count, sizeof *result_linkables_count)) ||
       (0 != readn(fd, result_linkables, (sizeof result_linkables[0]) *
                   UNSAFE_MIN(max_linkable_count, *result_linkables_count))))
    {
        return -1;
    }
    return 0;
}
