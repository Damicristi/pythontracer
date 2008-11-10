#!/usr/bin/env python

# Written by Eyal Lotem <eyal.lotem+pt@gmail.com>
# Copyright (2007-2008)
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

from __future__ import with_statement

import sys
import os
import traceback
import getopt
from pytracer import Tracer

from contextlib import nested

def exec_wrapper(python_program):
    def wrapper():
        g = {'__name__':'__main__'}
        try:
            execfile(python_program, g, g)
        except:
            print "Traced function completed with an exception:"
            traceback.print_exc()
        else:
            print "Traced function completed successfully"
    return wrapper

def usage():
    print """\
Tracing: %s [-h|--help] [-o|--output <output prefix>] [-s]
         <python script> <args>
Viewing: %s [-v|--view <input prefix>]

Tracing:
    -o or --output specify the prefix to use for generating the output
    filenames when running a trace. By default, if no prefix is given,
    "profile.out" will be used as a prefix.  This will generate two
    files: "profile.out" and "profile.out.index".

    If -s or --single is given, the trace will also be followed by the
    viewer.

Viewing:
    If -v or --view is given, then no trace will occur, and no output
    filename can be specified.  Instead, the trace viewer will be
    launched to view a previous trace result specified by the input
    prefix.
    
""" % (sys.argv[0], sys.argv[0])

def main():
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hso:v:", ["help", "single", "output=", "view="])
    except getopt.GetoptError, err:
        print str(err)
        usage()
        sys.exit(2)
    output_prefix = None
    view_prefix = None
    also_view = False
    for o, val in opts:
        if o in ("-h", "--help"):
            usage()
            sys.exit()
        elif o in ("-o", "--output"):
            output_prefix = val
        elif o in ("-v", "--view"):
            view_prefix = val
        elif o in ("-s", "--single"):
            also_view = True
        else:
            assert False, "unhandled option"
    if view_prefix is not None:
        # View mode:
        if output_prefix is not None or also_view or args:
            print "Cannot both view and output a trace."
            print "Use -s to trace & view"
            sys.exit(3)
    elif output_prefix is None:
        output_prefix = "profile.out"

    if output_prefix is not None:
        # Trace mode:
        if not args:
            print "No <python script> given"
            usage()
            sys.exit(4)
        sys.argv = args
        python_program = sys.argv[0]
        dirname = os.path.dirname(python_program)
        sys.path.insert(0, dirname)

        print "Tracing into %r" % (output_prefix,)
        with nested(open(output_prefix, "wb"),
                    open(output_prefix + '.index', "wb")) as (output_fileobj,
                                                              index_fileobj):
            tracer = Tracer(output_fileobj, index_fileobj)
            tracer.trace(exec_wrapper(python_program))
    if also_view:
        view_prefix = output_prefix
    if view_prefix is not None:
        # Don't depend on Gtk/viewer unless we must
        import pytracerview
        pytracerview.tracerview(view_prefix)

if __name__ == "__main__":
    main()
