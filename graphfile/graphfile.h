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

#ifndef __graphfile_h_
#define __graphfile_h_

#include "graphfile_internal.h"
#include <sys/types.h>
#include <stdint.h>

typedef struct graphfile_writer graphfile_writer_t;
typedef struct graphfile_reader graphfile_reader_t;
typedef struct graphfile_node graphfile_node_t;

/* All int return types return zero to indicate success */

/* An empty, seekable and writable file must be referenced by file.
 * Noone else must move the offset of the file while the writer is active
 * (until it is finalized). */
int graphfile_writer_init(graphfile_writer_t *graphfile_writer, FILE *);
/* This must be called to get a coherent file. */
int graphfile_writer_set_root(graphfile_writer_t *graphfile_writer,
                              graphfile_node_t *root);
void graphfile_writer_fini(graphfile_writer_t *graphfile_writer);

int graphfile_writer_write(graphfile_writer_t *graphfile_writer,
                           char *buffer, size_t buffer_length,
                           graphfile_node_t nodes[], uint32_t node_count,
                           graphfile_node_t *result_node);

/* A coherent, seekable and readable file must be referenced by file. */
int graphfile_reader_init(graphfile_reader_t *graphfile_reader, FILE *,
                          graphfile_node_t *result_root);
void graphfile_reader_fini(graphfile_reader_t *graphfile_reader);

int graphfile_reader_read(graphfile_reader_t *graphfile_reader,
                          graphfile_node_t *node,

                          char *result_buffer, size_t max_buffer_length,
                          size_t *result_buffer_length,

                          graphfile_node_t result_nodes[],
                          uint32_t max_node_count,
                          uint32_t *result_nodes_count);

#endif
