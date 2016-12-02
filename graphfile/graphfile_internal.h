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

#ifndef __graphfile_internal_h_
#define __graphfile_internal_h_

/* TODO: Clean this up into a 64-bit file access abstraction
 * library */
#include <sys/types.h>

#include <stdio.h>

#ifdef _LARGEFILE64_SOURCE
typedef off64_t graphfile_offset_t;
#define graphfile_seek lseek64
#else
typedef off_t graphfile_offset_t;
#define graphfile_seek lseek
#endif

struct graphfile_writer {
    FILE *file;
    graphfile_offset_t offset;
};

struct graphfile_reader {
    FILE *file;
};

struct graphfile_node {
    graphfile_offset_t offset;
};

#endif
