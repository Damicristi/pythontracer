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
    def on_get_path(self, (indices, nodes)):
        return tuple(indices)
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

def format_time(x):
    return '%.5f' % (x,)

class TraceReader(Model):
    def _get_user_time(self, (indices, nodes)):
        (code, (user_time, sys_time, real_time)), children = self._read(nodes[-1])
        return format_time(user_time)
    def _get_sys_time(self, (indices, nodes)):
        (code, (user_time, sys_time, real_time)), children = self._read(nodes[-1])
        return format_time(sys_time)
    def _get_real_time(self, (indices, nodes)):
        (code, (user_time, sys_time, real_time)), children = self._read(nodes[-1])
        return format_time(real_time/1000000.)
    def _get_namestr(self, (indices, nodes)):
        ((module_name, func_name, lineno), times), children = self._read(nodes[-1])
        return '%s(%d):%s' % (module_name, lineno, func_name)
    def _read(self, node):
        data, children = self.graph_reader.read(node)
        return loads(data), children
    column_getters = [_get_namestr, _get_user_time, _get_sys_time, _get_real_time]
    column_types = [str, str, str, str]
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
    def get_item(self, indices):
        for node in self.walk_path(indices):
            pass
        return self._read(node)
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

class TraceTree(object):
    def __init__(self, graph_reader):
        self.treestore = TraceReader(graph_reader)

        self.widget = gtk.ScrolledWindow()
        self.widget.set_policy(gtk.POLICY_AUTOMATIC,
                               gtk.POLICY_AUTOMATIC)
        
        self.tree_view = gtk.TreeView()
        self.tree_view.set_model(self.treestore)
        self.widget.add(self.tree_view)

        name_column = self._create_column('Name', 0)
        user_time_column = self._create_column('User Time', 1)
        system_time_column = self._create_column('System Time', 2)
        real_time_column = self._create_column('Real Time', 3)
#        name_column.set_sort_column_id(0)
        self.tree_view.set_search_column(0)

    def watch_cursor(self, callback):
        def cursor_changed(tree_view):
            path, column = self.tree_view.get_cursor()
            callback(self.treestore.get_item(path), column)
        self.tree_view.connect("cursor-changed", cursor_changed)

    def _create_column(self, title, column_id):
        cell = gtk.CellRendererText()
        column = gtk.TreeViewColumn(title)
        column.pack_start(cell, True)
#        column.set_max_width(400)
        column.add_attribute(cell, 'text', column_id)
        self.tree_view.append_column(column)
        return column

class CodePane(object):
    def __init__(self):
        self.widget = gtk.Frame('<filename>')
        self.scrolled_window = gtk.ScrolledWindow()
        self.scrolled_window.set_policy(gtk.POLICY_AUTOMATIC,
                                        gtk.POLICY_AUTOMATIC)
        self.text_buffer = gtk.TextBuffer()
        self.text_view = gtk.TextView(self.text_buffer)
        self.text_view.set_editable(False)
        self.highlighted_tag = self.text_buffer.create_tag(background="lightblue")
        self.scrolled_window.add(self.text_view)
        self.widget.add(self.scrolled_window)
        self._current_filename = None

    def watch(self, filename, lineno):
        if self._current_filename != filename:
            self._current_filename = filename
            self.text_buffer.set_text(open(filename, 'rb').read())
            self.widget.set_label(filename)
            self.last_tag = None

        if self.last_tag is not None:
            before_iter, after_iter = self.last_tag
            self.text_buffer.remove_tag(self.highlighted_tag, before_iter, after_iter)
        before_iter = self.text_buffer.get_iter_at_line_index(lineno, 0)
        after_iter = self.text_buffer.get_iter_at_line_index(lineno+1, 0)
        self.text_buffer.apply_tag(self.highlighted_tag, before_iter, after_iter)
        self.last_tag = before_iter, after_iter
        
        mark = self.text_buffer.create_mark('', before_iter)
        self.text_view.scroll_to_mark(mark, 0, use_align=True)

class TraceView(object):
    def __init__(self, execution_tree):
        self.widget = gtk.VPaned()
        self.trace_tree = TraceTree(execution_tree)
        self.code_pane = CodePane()
        self.widget.pack1(self.trace_tree.widget, resize=True)
        self.widget.pack2(self.code_pane.widget, resize=False)

        def callback(item, column):
            data, children = item
            (filename, funcname, lineno), times = data
            self.code_pane.watch(filename, lineno-1)
        self.trace_tree.watch_cursor(callback)
    def cursor_changed(self, *args):
        print "Cursor at", self.trace_tree.tree_view.get_cursor()

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
