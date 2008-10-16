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

struct graphfile_linkable {
    graphfile_offset_t offset;
};

#endif
