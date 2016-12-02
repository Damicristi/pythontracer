import sys
from reader import TraceReader

def usage():
    print("Usage: %s <path> [<prune depth>]" % (sys.argv[0],))
    sys.exit(1)

def dump(children, depth, indent=''):
    if depth == 0:
        return
    for child in children:
        print('%s%s:%s:%s took U%ss:S%ss:R%ss' % (
            indent, child.filename, child.lineno, child.name,
            child.user_time, child.sys_time, child.real_time))
        dump(child.children, depth-1, indent + '   ')

def main():
    if len(sys.argv) == 2:
        path, = sys.argv[1:]
        prune_depth = 5
    elif len(sys.argv) == 3:
        path, prune_depth_str = sys.argv[1:]
        try:
            prune_depth = int(prune_depth_str)
        except ValueError:
            usage()
    else:
        usage()
    reader = TraceReader(path)
    dump(reader.root_nodes, prune_depth)

if __name__ == '__main__':
    main()
