#ifndef __graphfile_h_
#define __graphfile_h_

#include "graphfile_internal.h"
#include <sys/types.h>

typedef struct graphfile_writer graphfile_writer_t;
typedef struct graphfile_reader graphfile_reader_t;
typedef struct graphfile_linkable graphfile_linkable_t;

/* All int return types return zero to indicate success */

/* An empty, seekable and writable file must be referenced by fd.
 * Noone else must move the offset of fd while the writer is active
 * (until it is finalized). */
int graphfile_writer_init(graphfile_writer_t *graphfile_writer, FILE *);
/* This must be called to get a coherent file. */
int graphfile_writer_set_root(graphfile_writer_t *graphfile_writer,
                              graphfile_linkable_t *root);
void graphfile_writer_fini(graphfile_writer_t *graphfile_writer);

int graphfile_writer_write(graphfile_writer_t *graphfile_writer,
                           char *buffer, size_t buffer_length,
                           graphfile_linkable_t linkables[], size_t linkable_count,
                           graphfile_linkable_t *result_linkable);

/* A coherent, seekable and readable file must be referenced by fd. */
int graphfile_reader_init(graphfile_reader_t *graphfile_reader, FILE *,
                          graphfile_linkable_t *result_root);
void graphfile_reader_fini(graphfile_reader_t *graphfile_reader);

int graphfile_reader_read(graphfile_reader_t *graphfile_reader,
                          graphfile_linkable_t *node,

                          char *result_buffer, size_t max_buffer_length,
                          size_t *result_buffer_length,
                          
                          graphfile_linkable_t result_linkables[], size_t max_linkable_count,
                          size_t *result_linkables_count);

#endif
