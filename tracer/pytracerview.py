#!/usr/bin/env python

import gtk
import sys
import struct
from graphfile import Reader
from marshal import loads

class AddFilterDialog(gtk.Dialog):
    def __init__(self):
        gtk.Dialog.__init__(self, "Add filter", buttons=(gtk.STOCK_OK, gtk.RESPONSE_OK,
                                                         gtk.STOCK_CANCEL, gtk.RESPONSE_REJECT))
        self.connect("response", self.handle_response)
        realtime_filter_box = gtk.HBox()
        realtime_filter_label = gtk.Label("Minimum real time shown")
        realtime_filter_box.add(realtime_filter_label)

        self.number = gtk.Adjustment(0, 0, 5, 0.001)

        realtime_filter_number_spinbox = gtk.SpinButton(self.number, climb_rate=0.001, digits=3)
        realtime_filter_box.add(realtime_filter_number_spinbox)

        realtime_filter_number_slider = gtk.HScale()
        realtime_filter_number_slider.set_adjustment(self.number)
        realtime_filter_number_slider.set_digits(5)
        realtime_filter_number_slider.set_size_request(300, -1)
        realtime_filter_box.add(realtime_filter_number_slider)

        self.vbox.add(realtime_filter_box)
    def handle_response(self, dialog, response_id):
        self.hide()



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

class TraceReader(Model):
    def __init__(self, graph_reader, root):
        self.graph_reader = graph_reader
        self.root = root
        Model.__init__(self)
    def on_get_flags(self):
        return gtk.TREE_MODEL_ITERS_PERSIST
    def on_iter_n_children(self, path):
        if path is None:
            path = ()
        data, children = self.read(path)
        return len(children)
    def on_iter_nth_child(self, path, n):
        if path is None:
            path = ()
        if n >= self.on_iter_n_children(path):
            return None
        return tuple(path) + (n,)

    _format = struct.Struct('16s16siddd')
    def _decode(self, data):
        if not data:
            return None
        filename, name, lineno, user_time, sys_time, real_time = self._format.unpack(data)
        return ((filename, name, lineno), (user_time, sys_time, real_time))

    def read_linkable(self, linkable):
        data, children = self.graph_reader.read(linkable)
        return self._decode(data), children
    def iter(self, path):
        cur = self.root
        for index in path:
            data, children = self.graph_reader.read(cur)
            cur = children[index]
        return cur
    def read(self, path):
        return self.read_linkable(self.iter(path))

    def format_time(self, x):
        return '%.5f' % (x,)
    def _get_user_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return self.format_time(user_time)
    def _get_sys_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return self.format_time(sys_time)
    def _get_real_time(self, path):
        (code, (user_time, sys_time, real_time)), children = self.read(path)
        return self.format_time(real_time/1000000.)
    def _get_namestr(self, path):
        ((module_name, func_name, lineno), times), children = self.read(path)
        return func_name
    def _get_filenamestr(self, path):
        ((module_name, func_name, lineno), times), children = self.read(path)
        return '%s(%d)' % (module_name, lineno)
    column_getters = [_get_filenamestr, _get_namestr, _get_user_time, _get_sys_time, _get_real_time]
    column_types = [str, str, str, str, str]

class TraceTree(gtk.ScrolledWindow):
    def __init__(self, graph_reader, root):
        gtk.ScrolledWindow.__init__(self)
        self._treestore = TraceReader(graph_reader, root)
        self.treestore = self._treestore.filter_new()
        self.treestore.set_visible_func(self._filter_func)

        self._min_realtime_filter = 0

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

    def _filter_func(self, model, iter):
        # TODO: Replace the literal column number
        real_time = float(model.get_value(iter, 4))
        return real_time >= self._min_realtime_filter

    def set_min_realtime_filter(self, min_real_time):
        self._min_realtime_filter = min_real_time
        self.treestore.refilter()

    def cursor_node(self):
        path, column = self.tree_view.get_cursor()
        return self._treestore.iter(path)

    def cursor(self):
        path, column = self.tree_view.get_cursor()
        return self._treestore.read(path), column

    def watch_cursor(self, callback):
        def cursor_changed(tree_view):
            item, column = self.cursor()
            callback(item, column)
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

    def ui_expand_and_jump_to_biggest(self):
        path, column = self.tree_view.get_cursor()
        self.tree_view.expand_row(path, False)
        data, children = self._treestore.read(path)
        def child_times(index, child):
            (code, (user_time, sys_time, real_time)), children = self._treestore.read_linkable(child)
            return (real_time, index)
        if children:
            max_real_time, max_index = max(child_times(index, child) for index, child in enumerate(children))
            self.tree_view.set_cursor(path + (max_index,))

    def handle_response(self, dialog, response):
        if gtk.RESPONSE_OK == response:
            value = dialog.number.get_value()
            self.set_min_realtime_filter(value)
        dialog.destroy()

    def ui_set_min_realtime_filter(self):
        dialog = AddFilterDialog()
        dialog.connect("response", self.handle_response)
        dialog.show_all()

    def ui_collapse(self):
        path, column = self.tree_view.get_cursor()
        if self.tree_view.row_expanded(path):
            self.tree_view.collapse_row(path)
        else:
            self.tree_view.set_cursor(path[:-1])
    def ui_expand(self):
        path, column = self.tree_view.get_cursor()
        if not self.treestore.iter_has_child(self.treestore.get_iter(path)):
            return
        self.tree_view.expand_row(path, False)
        self.tree_view.set_cursor(path + (0,))

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
                print repr(filename)
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
    def __init__(self, app, graph_reader, root):
        gtk.VPaned.__init__(self)
        self.app = app
        self.graph_reader = graph_reader
        self.trace_tree = TraceTree(self.graph_reader, root)
        self.code_pane = CodePane()
        self.pack1(self.trace_tree, resize=True)
        self.pack2(self.code_pane, resize=False)

        def callback(item, column):
            data, children = item
            (filename, funcname, lineno), times = data
            self.code_pane.watch(filename, lineno-1)
        self.trace_tree.watch_cursor(callback)

    def ui_expand_and_jump_to_biggest(self):
        self.trace_tree.ui_expand_and_jump_to_biggest()
    def ui_set_min_realtime_filter(self):
        self.trace_tree.ui_set_min_realtime_filter()
    def ui_collapse(self):
        self.trace_tree.ui_collapse()
    def ui_expand(self):
        self.trace_tree.ui_expand()
    def ui_new_window(self):
        (((filename, funcname, lineno), times), children), column = self.trace_tree.cursor()
        self.app.new_window(self.graph_reader,
                            self.trace_tree.cursor_node(),
                            ':%s:%s' % (filename, funcname))

class Application(object):
    def __init__(self, graph_reader, root):
        self._window_count = 0
        self.new_window(graph_reader, root, '')

    def new_window(self, graph_reader, root, suffix):
        trace_view = TraceView(self, graph_reader, root)
        ag = gtk.AccelGroup()
        ag.connect_group(gtk.keysyms.q, gtk.gdk.CONTROL_MASK, 0, gtk.main_quit)

        def drop_args_func(func):
            def new_func(*args):
                return func()
            return new_func

        def set_shortcut_key(func, key, mod=0):
            ag.connect_group(key, mod, 0, drop_args_func(func))

        set_shortcut_key(trace_view.ui_expand_and_jump_to_biggest, gtk.keysyms.o)
        set_shortcut_key(trace_view.ui_set_min_realtime_filter,    gtk.keysyms.question)
        set_shortcut_key(trace_view.ui_collapse,                   gtk.keysyms.bracketleft)
        set_shortcut_key(trace_view.ui_expand,                     gtk.keysyms.bracketright)
        set_shortcut_key(trace_view.ui_new_window,                 gtk.keysyms.n)

        # Create a new window
        window = gtk.Window(gtk.WINDOW_TOPLEVEL)
        window.add_accel_group(ag)

        window.set_title("Trace view" + suffix)
        window.set_size_request(600, 400)
        window.connect("delete_event", self._window_closed)
        window.add(trace_view)
        window.show_all()
        self._window_count += 1
        return window

    def _window_closed(self, *args):
        assert self._window_count >= 1
        self._window_count -= 1
        if self._window_count == 0:
            gtk.main_quit()

    def main(self):
        gtk.main()

def main():
    filename, = sys.argv[1:]
    graph_reader = Reader(open(filename, "rb"))

    app = Application(graph_reader, graph_reader.root)
    app.main()

if __name__ == "__main__":
    main()
