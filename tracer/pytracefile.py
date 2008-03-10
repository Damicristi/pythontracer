#!/usr/bin/env python

import sys
import os
from pytracer import Tracer

def main():
    tracer = Tracer(open("profile.out", "wb"))
    tracer_cmd = sys.argv.pop(0)
    python_program = sys.argv[0]
    g = {'__name__':'__main__'}
    tracer.trace(lambda : execfile(python_program, g, g))

if __name__ == '__main__':
    main()
