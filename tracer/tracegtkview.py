#!/usr/bin/env python

import gtk
import sys
from pygraphfile import Reader
from marshal import loads

class Model(gtk.GenericTreeModel):
    # rowref <-> path are the same here
    def on_get_n_columns(self):
        return len(self.column_types)
    def on_get_column_type(self, index):
        return self.column_types[index]
    def on_get_iter(self, path):
        return path
    def on_get_path(self, path):
        return tuple(path)
    def on_get_value(self, path, column):
        return self.column_getters[column](self, path)
    def on_iter_children(self, path):
        return self.on_iter_nth_child(path, 0)
    def on_iter_has_child(self, path):
        return bool(self.on_iter_n_children(path))
    def on_iter_next(self, path):
        parent = self.on_iter_parent(path)
        if path[-1]+1 >= self.on_iter_n_children(parent):
            return None
        return self.on_iter_nth_child(parent, path[-1]+1)
    def on_iter_parent(self, path):
        return path[:-1]

def format_time(x):
    return '%.5f' % (x,)

class TraceReader(Model):
    def _get_user_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return format_time(user_time)
    def _get_sys_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return format_time(sys_time)
    def _get_real_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return format_time(real_time/1000000.)
    def _get_namestr(self, path):
        ((module_name, func_name, lineno), times), children = self.read(path)
        return '%s(%d):%s' % (module_name, lineno, func_name)
    def read(self, path):
        cur = self.graph_reader.root
        for index in path:
            data, children = self.graph_reader.read(cur)
            cur = children[index]

        data, children = self.graph_reader.read(cur)
        return loads(data), children
    column_getters = [_get_namestr, _get_user_time, _get_sys_time, _get_real_time]
    column_types = [str, str, str, str]
    def __init__(self, graph_reader):
        self.graph_reader = graph_reader
        Model.__init__(self)
    def on_get_flags(self):
        return gtk.TREE_MODEL_ITERS_PERSIST
    def on_iter_n_children(self, path):
        data, children = self.read(path)
        return len(children)
    def on_iter_nth_child(self, path, n):
        if path is None:
            return self.on_get_iter([n])
        return tuple(path) + (n,)

class TraceTree(object):
    def __init__(self, graph_reader):
        self.treestore = TraceReader(graph_reader)

        self.widget = gtk.ScrolledWindow()
        self.widget.set_policy(gtk.POLICY_AUTOMATIC,
                               gtk.POLICY_AUTOMATIC)
        
        self.tree_view = gtk.TreeView()
        self.tree_view.set_property('enable-search', False)
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
            callback(self.treestore.read(path), column)
        self.tree_view.connect("cursor-changed", cursor_changed)

    def _create_column(self, title, column_id):
        cell = gtk.CellRendererText()
        column = gtk.TreeViewColumn(title)
        column.pack_start(cell, True)
#        column.set_max_width(400)
        column.add_attribute(cell, 'text', column_id)
        column.set_sizing(gtk.TREE_VIEW_COLUMN_AUTOSIZE)
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
