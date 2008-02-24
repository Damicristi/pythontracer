#ifndef __graphfile_internal_h_
#define __graphfile_internal_h_

typedef unsigned long long graphfile_offset_t;

struct graphfile_writer {
    int fd;
};

struct graphfile_reader {
    int fd;
};

struct graphfile_linkable {
    graphfile_offset_t offset;
};

#endif
