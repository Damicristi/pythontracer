#!/usr/bin/env python

import gtk
import sys
from pygraphfile import Reader
from marshal import loads

class Model(gtk.GenericTreeModel):
    # In a (indices, nodes) tuple:
    # len(nodes) == len(indices)+1
    # nodes = [root] + [children_for_each_of_indices]
    def on_get_n_columns(self):
        return len(self.column_types)
    def on_get_column_type(self, index):
        return self.column_types[index]
    def on_get_iter(self, indices):
        return indices, list(self.walk_path(indices))
    def on_get_path(self, (indices, node)):
        return indices
    def on_get_value(self, rowref, column):
        return self.column_getters[column](self, rowref)
    def on_iter_children(self, (indices, nodes)):
        return self.on_iter_nth_child((indices, nodes), 0)
    def on_iter_has_child(self, rowref):
        return bool(self.on_iter_n_children(rowref))
    def on_iter_next(self, (indices, nodes)):
        parent = self.on_iter_parent((indices, nodes))
        return self.on_iter_nth_child(parent, indices[-1]+1)
    def on_iter_parent(self, (indices, nodes)):
        return (indices[:-1], nodes[:-1])

def millionth(x):
    return '%.5f' % (x/1000000.)

class TraceReader(Model):
    def _get_cpu_time(self, (indices, nodes)):
        ((module_name, func_name), (cpu_time, real_time)), children = self._read(nodes[-1])
        return millionth(cpu_time)
    def _get_real_time(self, (indices, nodes)):
        ((module_name, func_name), (cpu_time, real_time)), children = self._read(nodes[-1])
        return millionth(real_time)
    def _get_namestr(self, (indices, nodes)):
        ((module_name, func_name), (cpu_time, real_time)), children = self._read(nodes[-1])
        return '%s:%s' % (module_name, func_name)
    def _read(self, node):
        data, children = self.graph_reader.read(node)
        return loads(data), children
    column_getters = [_get_namestr, _get_real_time, _get_cpu_time]
    column_types = [str, str, str]
    def __init__(self, graph_reader):
        self.graph_reader = graph_reader
        Model.__init__(self)
    def on_get_flags(self):
        return gtk.TREE_MODEL_ITERS_PERSIST
    def walk_path(self, indices):
        cur = self.graph_reader.root
        yield cur
        for index in indices:
            data, children = self.graph_reader.read(cur)
            cur = children[index]
            yield cur
    def on_iter_n_children(self, (indices, nodes)):
        data, children = self.graph_reader.read(nodes[-1])
        return len(children)
    def on_iter_nth_child(self, rowref, n):
        if rowref is None:
            return self.on_get_iter([n])
        indices, nodes = rowref
        data, children = self.graph_reader.read(nodes[-1])
        if n >= len(children):
            return None
        return (list(indices) + [n],
                list(nodes) + [children[n]])

class TraceView(object):
    def __init__(self, graph_reader):
        self.treestore = TraceReader(graph_reader)

        self.widget = gtk.ScrolledWindow()
        
        self.tree_view = gtk.TreeView()
        self.tree_view.set_model(self.treestore)
        self.widget.add(self.tree_view)

        name_column = self._create_column('Name', 0)
        real_time_column = self._create_column('Real Time', 1)
        cpu_time_column = self._create_column('CPU Time', 2)
        name_column.set_sort_column_id(0)
        self.tree_view.set_search_column(0)

    def _create_column(self, title, column_id):
        cell = gtk.CellRendererText()
        column = gtk.TreeViewColumn(title)
        column.pack_start(cell, True)
#        column.set_max_width(400)
        column.add_attribute(cell, 'text', column_id)
        self.tree_view.append_column(column)
        return column

def main():
    filename, = sys.argv[1:]
    execution_tree = Reader(open(filename, "rb"))
    trace_view = TraceView(execution_tree)

    # Create a new window
    window = gtk.Window(gtk.WINDOW_TOPLEVEL)
    window.set_title("Trace view")
    window.set_size_request(600, 400)
    window.connect("delete_event", gtk.main_quit)
    window.add(trace_view.widget)
    window.show_all()
    gtk.main()

if __name__ == "__main__":
    main()
