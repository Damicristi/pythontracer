/* Written by Eyal Lotem <eyal.lotem+pt@gmail.com>
 * Copyright (2007-2008)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "graphfile.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
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


#define GNUMBER_BARKER_SIZE	(3)
#define GNUMBER_BARKER		((1UL<<(8*GNUMBER_BARKER_SIZE))-1)
static unsigned char gnumber_barker[GNUMBER_BARKER_SIZE] = { 0xFF, 0xFF, 0xFF };

static graphfile_size_t write_gnumber(FILE *f, uint64_t number64)
{
    /* Endianness is crap :-(
       To overcome it, lets do this: */
    if(number64 < GNUMBER_BARKER) {
        unsigned char gnumber[GNUMBER_BARKER_SIZE] = {
            (uint8_t)(number64 >> 0),
            (uint8_t)(number64 >> 8),
            (uint8_t)(number64 >> 16)
        };
        IF_ERR_RETURN(writen(f, gnumber, sizeof gnumber));
        return sizeof gnumber;
    }
    IF_ERR_RETURN(writen(f, gnumber_barker, sizeof gnumber_barker));
    IF_ERR_RETURN(writen(f, &number64, sizeof number64));
    return sizeof gnumber_barker + sizeof number64;
}

static graphfile_size_t read_gnumber(FILE *f, uint64_t *p_number64)
{
    unsigned char gnumber[GNUMBER_BARKER_SIZE];

    IF_ERR_RETURN(readn(f, gnumber, sizeof gnumber));
    if(0 != memcmp(gnumber, gnumber_barker, GNUMBER_BARKER_SIZE)) {
        (*p_number64) = ((((uint64_t)gnumber[0]) << 0) +
                         (((uint64_t)gnumber[1]) << 8) +
                         (((uint64_t)gnumber[2]) << 16));
        return sizeof gnumber;
    }

    IF_ERR_RETURN(readn(f, p_number64, sizeof *p_number64));
    return sizeof gnumber + sizeof *p_number64;
}


static int safe_fileno(FILE *f) {
    /* Must fflush before messing with the fd of a (FILE*) */
    if(0 != fflush(f)) {
        return -1;
    }
    /* May return -1 */
    return fileno(f);
}

static int seek(FILE *f, graphfile_offset_t offset) {
    int fd = safe_fileno(f);
    IF_ERR_RETURN(fd);
    if(((graphfile_offset_t)-1) == graphfile_seek(fd, offset, SEEK_SET)) {
        return -1;
    }
    return 0;
}

static graphfile_offset_t tell(FILE *f) {
    int fd = safe_fileno(f);
    IF_ERR_RETURN(fd);
    return graphfile_seek(fd, 0, SEEK_CUR);
}

int graphfile_writer_init(graphfile_writer_t *graphfile_writer, FILE *file)
{
    graphfile_offset_t offset;
    graphfile_writer->file = file;
    if(-1 == fseek(file, 0, SEEK_END)) {
        /* A seekable file must be used */
        return -1;
    }
    offset = tell(file);
    if(((graphfile_offset_t)-1 == offset) || (offset > 0)) {
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
    graphfile_offset_t offset = graphfile_writer->offset;

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
    uint64_t buffer_length;
    uint64_t linkables_count;
    graphfile_size_t size;
    FILE *file = graphfile_reader->file;
    IF_ERR_RETURN(seek(file, node->offset));
    IF_ERR_RETURN(size = read_gnumber(file, &buffer_length));
    IF_ERR_RETURN(readn(file, result_buffer, UNSAFE_MIN(max_buffer_length, buffer_length)));
    IF_ERR_RETURN(seek(file, node->offset + size + buffer_length));
    IF_ERR_RETURN(read_gnumber(file, &linkables_count));
    min_linkable_count = UNSAFE_MIN(max_linkable_count, linkables_count);
    for(i = 0; i < min_linkable_count; ++i) {
        IF_ERR_RETURN(read_gnumber(file, &relative_offset));
        result_linkables[i].offset = node->offset - relative_offset;
    }

    (*result_linkables_count) = linkables_count;
    (*result_buffer_length) = buffer_length;

    return 0;
}
