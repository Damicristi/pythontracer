import sys
from time import time, clock
from cPickle import dump
from ExecutionTree import ExecutionTree
from pygraphfile import Writer

def times():
    return clock(), time()

class Tracer(object):
    def __init__(self, fileobj):
        self.writer = Writer(fileobj)
        self.execution_stack = [ExecutionTree()]
    def trace_func(self, func):
        sys.settrace(self._trace_wrapper)
        try:
            return func()
        finally:
            sys.settrace(None)
            root = self._write(self.execution_stack.pop())
            assert not self.execution_stack
            self.writer.set_root(root)
    def _write(self, node):
        return self.writer.write(str(node), node.children)

    def _trace_wrapper(self, frame, actionstr, arg):
        try:
            return self._trace(frame, actionstr, arg)
        except:
            import traceback
            traceback.print_exc()
            return None
    def _trace(self, frame, actionstr, arg):
        if actionstr == 'call':
            execution = ExecutionTree(frame)
            execution.start_times = times()
            self.execution_stack.append(execution)
            return self._trace_wrapper
        elif actionstr == 'return':
            node = self.execution_stack.pop()
            node.stop_times = times()
            child = self._write(node)
            self.execution_stack[-1].children.append(child)
#         else:
#             print actionstr, "ignored"

def main():
    tracer = Tracer(open("profile.out", "wb"))
    python_program = sys.argv.pop(1)
    g = {'__name__':'__main__'}
    tracer.trace_func(lambda : execfile(python_program, g, g))

if __name__ == '__main__':
    main()
