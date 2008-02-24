#include "graphfile.h"

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

static int writen(FILE *f, const void *buffer, size_t buffer_size)
{
    /* TODO: Really writen here... */
    if(buffer_size != fwrite(buffer, 1, buffer_size, f)) {
        return -1;
    }
    return 0;
}

static int readn(FILE *f, void *buffer, size_t buffer_size)
{
    /* TODO: Really readn here... */
    if(buffer_size != fread(buffer, 1, buffer_size, f)) {
        return -1;
    }
    return 0;
}

static int seek(FILE *f, long offset) {
    if(0 != fseek(f, offset, SEEK_SET)) {
        return -1;
    }
    if(offset != ftell(f)) {
        return -1;
    }
    return 0;
}

int graphfile_writer_init(graphfile_writer_t *graphfile_writer, FILE *file)
{
    long offset;
    graphfile_writer->file = file;
    if(-1 == fseek(file, 0, SEEK_END)) {
        /* A seekable file must be used */
        return -1;
    }
    offset = ftell(file);
    if((-1 == offset) || (offset > 0)) {
        /* An empty file must be used */
        return -1;
    }
    
    /* POSIX allows seeking to beyond the end of the file */
    if(0 != seek(file, sizeof(graphfile_linkable_t))) {
        return -1;
    }
    return 0;
}

int graphfile_writer_set_root(graphfile_writer_t *graphfile_writer,
                              graphfile_linkable_t *root)
{
    FILE *file = graphfile_writer->file;
    if(0 != seek(file, 0)) {
        return -1;
    }
    if(0 != writen(file, root, sizeof *root)) {
        return -1;
    }
    if(0 != fseek(file, 0, SEEK_END)) {
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
    FILE *file = graphfile_writer->file;
    long offset = ftell(file);
    if(-1 == offset) {
        return -1;
    }
    if((0 != writen(file, &buffer_length, sizeof buffer_length)) ||
       (0 != writen(file, buffer, buffer_length)) ||
       (0 != writen(file, &linkable_count, sizeof linkable_count)) ||
       (0 != writen(file, linkables, (sizeof linkables[0])*linkable_count)))
    {
        return -1;
    }
    result_linkable->offset = offset;
    return 0;
}


int graphfile_reader_init(graphfile_reader_t *graphfile_reader, FILE *file,
                          graphfile_linkable_t *result_root)
{
    graphfile_reader->file = file;
    if(0 != seek(file, 0)) {
        /* A seekable file must be used */
        return -1;
    }
    if(0 != readn(file, result_root, sizeof *result_root)) {
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
    FILE *file = graphfile_reader->file;
    if(0 != seek(file, node->offset)) {
        return -1;
    }
    if((0 != readn(file, result_buffer_length, sizeof *result_buffer_length)) ||
       (0 != readn(file, result_buffer, UNSAFE_MIN(max_buffer_length, *result_buffer_length))))
    {
        return -1;
    }
    if((0 != seek(file, node->offset + (sizeof *result_buffer_length) + *result_buffer_length)) ||
       (0 != readn(file, result_linkables_count, sizeof *result_linkables_count)) ||
       (0 != readn(file, result_linkables, (sizeof result_linkables[0]) *
                   UNSAFE_MIN(max_linkable_count, *result_linkables_count))))
    {
        return -1;
    }
    return 0;
}
