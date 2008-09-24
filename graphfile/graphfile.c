#include "graphfile.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

#define IF_ERR_RETURN(result) do { if(-1 == (result)) return -1; } while(0)

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


static uint32_t barker32 = -1UL;
static uint16_t barker16 = (uint16_t)-1UL;

static int write_gnumber(FILE *f, uint64_t number64)
{
    /* Endianness is crap :-(
       To overcome it, lets do this: */
    uint32_t number32 = number64;
    uint16_t number16 = number64;
    if(number64 < barker16) {
        IF_ERR_RETURN(writen(f, &number16, sizeof number16));
        return sizeof number16;
    }
    IF_ERR_RETURN(writen(f, &barker16, sizeof barker16));
    if(number64 < barker32) {
        IF_ERR_RETURN(writen(f, &number32, sizeof number32));
        return sizeof barker16 + sizeof number32;
    }
    IF_ERR_RETURN(writen(f, &barker32, sizeof barker32));
    IF_ERR_RETURN(writen(f, &number64, sizeof number64));
    return sizeof barker16 + sizeof barker32 + sizeof number64;
}

static int read_gnumber(FILE *f, uint64_t *p_number64)
{
    uint32_t number32;
    uint16_t number16;

    IF_ERR_RETURN(readn(f, &number16, sizeof number16));
    if(number16 != barker16) {
        (*p_number64) = number16;
        return sizeof number16;
    }

    IF_ERR_RETURN(readn(f, &number32, sizeof number32));
    if(number32 != barker32) {
        (*p_number64) = number32;
        return sizeof number16 + sizeof number32;
    }

    IF_ERR_RETURN(readn(f, p_number64, sizeof *p_number64));
    return sizeof number16 + sizeof number32 + sizeof *p_number64;
}


static int safe_fileno(FILE *f) {
    /* Must fflush before messing with the fd of a (FILE*) */
    if(0 != fflush(f)) {
        return -1;
    }
    /* May return -1 */
    return fileno(f);
}

static int seek(FILE *f, off64_t offset) {
    int fd = safe_fileno(f);
    IF_ERR_RETURN(fd);
    if(((off64_t)-1) == lseek64(fd, offset, SEEK_SET)) {
        return -1;
    }
    return 0;
}

static off64_t tell(FILE *f) {
    int fd = safe_fileno(f);
    IF_ERR_RETURN(fd);
    return lseek64(fd, 0, SEEK_CUR);
}

int graphfile_writer_init(graphfile_writer_t *graphfile_writer, FILE *file)
{
    off64_t offset;
    graphfile_writer->file = file;
    if(-1 == fseek(file, 0, SEEK_END)) {
        /* A seekable file must be used */
        return -1;
    }
    offset = tell(file);
    if(((off64_t)-1 == offset) || (offset > 0)) {
        /* An empty file must be used */
        return -1;
    }

    /* POSIX allows seeking to beyond the end of the file */
    IF_ERR_RETURN(seek(file, sizeof(graphfile_linkable_t)));
    graphfile_writer->offset = sizeof(graphfile_linkable_t);
    return 0;
}

int graphfile_writer_set_root(graphfile_writer_t *graphfile_writer,
                              graphfile_linkable_t *root)
{
    FILE *file = graphfile_writer->file;
    IF_ERR_RETURN(seek(file, 0));
    IF_ERR_RETURN(writen(file, root, sizeof *root));
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
                           char *buffer, graphfile_size_t buffer_length,
                           graphfile_linkable_t linkables[], graphfile_size_t linkable_count,
                           graphfile_linkable_t *result_linkable)
{
    graphfile_size_t i;
    graphfile_size_t size;
    FILE *file = graphfile_writer->file;
    off64_t offset = graphfile_writer->offset;

    /* TODO: Clean up all this code duplication */
    IF_ERR_RETURN(size = write_gnumber(file, buffer_length));
    graphfile_writer->offset += size;

    IF_ERR_RETURN(writen(file, buffer, buffer_length));
    graphfile_writer->offset += buffer_length;

    IF_ERR_RETURN(size = write_gnumber(file, linkable_count));
    graphfile_writer->offset += size;

    for(i = 0; i < linkable_count; ++i) {
        IF_ERR_RETURN(size = write_gnumber(file, offset - linkables[i].offset));
        graphfile_writer->offset += size;
    }
    result_linkable->offset = offset;
    return 0;
}


int graphfile_reader_init(graphfile_reader_t *graphfile_reader, FILE *file,
                          graphfile_linkable_t *result_root)
{
    graphfile_reader->file = file;

    /* A seekable file must be used */
    IF_ERR_RETURN(seek(file, 0));

    /* A readable, coherent file must be used, so it must have a
     * readable root. */
    IF_ERR_RETURN(readn(file, result_root, sizeof *result_root));

    if(0 == result_root->offset) {
        /* Root cannot be 0. If it is 0, it means that the file was
         * never set_root'd properly, and is corrupt. */
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

                          char *result_buffer, graphfile_size_t max_buffer_length,
                          graphfile_size_t *result_buffer_length,

                          graphfile_linkable_t result_linkables[], graphfile_size_t max_linkable_count,
                          graphfile_size_t *result_linkables_count)
{
    graphfile_size_t i;
    graphfile_size_t min_linkable_count;
    uint64_t relative_offset;
    graphfile_size_t size;
    FILE *file = graphfile_reader->file;
    IF_ERR_RETURN(seek(file, node->offset));
    IF_ERR_RETURN(size = read_gnumber(file, result_buffer_length));
    IF_ERR_RETURN(readn(file, result_buffer, UNSAFE_MIN(max_buffer_length, *result_buffer_length)));
    IF_ERR_RETURN(seek(file, node->offset + size + *result_buffer_length));
    IF_ERR_RETURN(read_gnumber(file, result_linkables_count));
    min_linkable_count = UNSAFE_MIN(max_linkable_count, *result_linkables_count);
    for(i = 0; i < min_linkable_count; ++i) {
        IF_ERR_RETURN(read_gnumber(file, &relative_offset));
        result_linkables[i].offset = node->offset - relative_offset;
    }

    return 0;
}
