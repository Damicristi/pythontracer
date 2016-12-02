import struct
_short_fmt = struct.Struct('H')

class _TraceEntry(object):
    def __init__(self, code_pos, times, children):
        self.filename, self.name, self.lineno = code_pos
        self.user_time, self.sys_time, self.real_time = times
        self.children = children
    def __repr__(self):
        return "%s (%s:%s): (user_time=%gs, sys_time=%gs, real_time=%gs): %s children" % (
            self.name, self.filename, self.lineno,
            self.user_time/1000000.,
            self.sys_time/1000000.,
            self.real_time/1000000., len(self.children))

class TraceReader(object):
    @staticmethod
    def read_string(fileobj):
        data = fileobj.read(_short_fmt.size)
        length, = _short_fmt.unpack(data)
        return fileobj.read(length).decode('utf8')

    @staticmethod
    def read_code_index(fileobj):
        code_index = {}
        while True:
            data = fileobj.read(_short_fmt.size)
            if not data:
                break
            index, = _short_fmt.unpack(data)
            filename = TraceReader.read_string(fileobj)
            name = TraceReader.read_string(fileobj)
            code_index[index] = filename, name
        return code_index

    def __init__(self, filename):
        self.code_index = TraceReader.read_code_index(open(filename+'.index', "rb"))
        from graphfile import Reader
        self.graph_reader = Reader(filename)
        data, children = self.graph_reader.read(self.graph_reader.root)
        assert self._decode(data) is None, "Root has data?"
        self.root_nodes = self._children_loader(children)

    _format = struct.Struct('hiddd')
    def _decode(self, data):
        if not data:
            return None
        code_index, lineno, user_time, sys_time, real_time = self._format.unpack(data)
        filename, name = self.code_index[code_index]
        return (filename, name, lineno), (user_time, sys_time, real_time)
    def _children_loader(self, children):
        class ChildrenLoader(object):
            def __repr__(self):
                return "ChildrenLoader(%s children)" % (len(children),)
            def __getitem__(inner_self, i):
                return self._read_node(children[i])
            def __len__(inner_self):
                return len(children)
        return ChildrenLoader()
    def _read_node(self, node):
        data, children = self.graph_reader.read(node)
        code_pos, times = self._decode(data)
        return _TraceEntry(code_pos, times, self._children_loader(children))
