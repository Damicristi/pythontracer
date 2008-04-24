#ifndef __graphfile_internal_h_
#define __graphfile_internal_h_

/* TODO: Clean this up into an abstraction library */
#define _LARGEFILE64_SOURCE
#include <sys/types.h>

#include <stdio.h>

struct graphfile_writer {
    FILE *file;
};

struct graphfile_reader {
    FILE *file;
};

struct graphfile_linkable {
    off64_t offset;
};

#endif
