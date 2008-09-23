cdef extern from "rotatingtree.h":
    ctypedef struct rotating_node_t
    rotating_node_t *EMPTY_ROTATING_TREE
    ctypedef int (*rotating_tree_enum_fn)(rotating_node_t *node, void *arg)
    void RotatingTree_Add(rotating_node_t **root, rotating_node_t *node)
    rotating_node_t* RotatingTree_Get(rotating_node_t **root, void *key)
    int RotatingTree_Enum(rotating_node_t *root, rotating_tree_enum_fn enumfn, void *arg)
