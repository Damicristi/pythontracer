#ifndef __graphfile_internal_h_
#define __graphfile_internal_h_

#include <stdio.h>

typedef unsigned long long graphfile_offset_t;

struct graphfile_writer {
    FILE *file;
};

struct graphfile_reader {
    FILE *file;
};

struct graphfile_linkable {
    graphfile_offset_t offset;
};

#endif
