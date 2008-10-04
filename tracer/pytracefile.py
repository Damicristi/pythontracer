#!/usr/bin/env python

import sys
import os
import traceback
from pytracer import Tracer

VERSION = "8.10.4"

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

def main():
    prog_name = sys.argv.pop(0)

    output_filename = 'profile.out'
    if sys.argv[0].startswith('-o'):
        output_opt = sys.argv.pop(0)
        if len(output_opt) > 2:
            output_filename = output_opt[2:]
        else:
            output_filename = sys.argv.pop(0)
    print "Tracer version %s: Tracing into %r" % (VERSION, output_filename)

    assert not sys.argv[0].startswith('-'), "Unknown option %r" % (sys.argv[0],)

    tracer = Tracer(open(output_filename, "wb"),
                    open(output_filename + '.index', "wb"))

    python_program = sys.argv[0]
    dirname = os.path.dirname(python_program)
    sys.path.insert(0, dirname)

    tracer.trace(exec_wrapper(python_program))

if __name__ == '__main__':
    main()
