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
        return func_name
    def _get_filenamestr(self, path):
        ((module_name, func_name, lineno), times), children = self.read(path)
        return '%s(%d)' % (module_name, lineno)
    def read_linkable(self, linkable):
        data, children = self.graph_reader.read(linkable)
        return loads(data), children
    def read(self, path):
        cur = self.graph_reader.root
        for index in path:
            data, children = self.graph_reader.read(cur)
            cur = children[index]

        return self.read_linkable(cur)
    column_getters = [_get_filenamestr, _get_namestr, _get_user_time, _get_sys_time, _get_real_time]
    column_types = [str, str, str, str, str]
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

class TraceTree(gtk.ScrolledWindow):
    def __init__(self, graph_reader):
        gtk.ScrolledWindow.__init__(self)
        self.treestore = TraceReader(graph_reader)

        self.set_policy(gtk.POLICY_AUTOMATIC,
                        gtk.POLICY_AUTOMATIC)

        self.tree_view = gtk.TreeView()
        self.tree_view.set_property('enable-search', False)
        self.tree_view.set_model(self.treestore)
        self.add(self.tree_view)

        filename_column = self._create_column('Filename', 0)
        name_column = self._create_column('Name', 1)
        user_time_column = self._create_column('User Time', 2)
        system_time_column = self._create_column('System Time', 3)
        real_time_column = self._create_column('Real Time', 4)
#        name_column.set_sort_column_id(0)
#        self.tree_view.set_search_column(0)

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

    def expand_and_jump_to_biggest(self):
        path, column = self.tree_view.get_cursor()
        self.tree_view.expand_row(path, False)
        data, children = self.treestore.read(path)
        def child_times(index, child):
            (code, (user_time, sys_time, real_time)), children = self.treestore.read_linkable(child)
            return (real_time, index)
        if children:
            max_real_time, max_index = max(child_times(index, child) for index, child in enumerate(children))
            self.tree_view.set_cursor(path + (max_index,))

class CodePane(gtk.Frame):
    def __init__(self):
        gtk.Frame.__init__(self, '<filename>')
        self.scrolled_window = gtk.ScrolledWindow()
        self.scrolled_window.set_policy(gtk.POLICY_AUTOMATIC,
                                        gtk.POLICY_AUTOMATIC)
        self.text_buffer = gtk.TextBuffer()
        self.text_view = gtk.TextView(self.text_buffer)
        self.text_view.set_editable(False)
        self.highlighted_tag = self.text_buffer.create_tag(background="lightblue")
        self.scrolled_window.add(self.text_view)
        self.add(self.scrolled_window)
        self._current_filename = None

    def watch(self, filename, lineno):
        if self._current_filename != filename:
            self._current_filename = filename
            try:
                data = open(filename, 'rb').read()
            except (OSError, IOError):
                data = "Error: Cannot read %r" % (filename,)
            self.text_buffer.set_text(data)
            self.set_label(filename)
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

class TraceView(gtk.VPaned):
    def __init__(self, execution_tree):
        gtk.VPaned.__init__(self)
        self.trace_tree = TraceTree(execution_tree)
        self.code_pane = CodePane()
        self.pack1(self.trace_tree, resize=True)
        self.pack2(self.code_pane, resize=False)

        def callback(item, column):
            data, children = item
            (filename, funcname, lineno), times = data
            self.code_pane.watch(filename, lineno-1)
        self.trace_tree.watch_cursor(callback)

    def expand_and_jump_to_biggest(self):
        self.trace_tree.expand_and_jump_to_biggest()

def main():
    filename, = sys.argv[1:]
    execution_tree = Reader(open(filename, "rb"))
    trace_view = TraceView(execution_tree)

    # Create a new window
    window = gtk.Window(gtk.WINDOW_TOPLEVEL)

    ag = gtk.AccelGroup()
    ag.connect_group(gtk.keysyms.q, gtk.gdk.CONTROL_MASK, 0, gtk.main_quit)
    def expand_and_jump_to_biggest(accel_group, window, key, flags):
        trace_view.expand_and_jump_to_biggest()
    ag.connect_group(gtk.keysyms.o, 0, 0, expand_and_jump_to_biggest)
    window.add_accel_group(ag)

    window.set_title("Trace view")
    window.set_size_request(600, 400)
    window.connect("delete_event", gtk.main_quit)
    window.add(trace_view)
    window.show_all()
    gtk.main()

if __name__ == "__main__":
    main()
