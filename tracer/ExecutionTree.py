class ExecutionTree(object):
    def __init__(self, frame=None):
        if frame is not None:
            self.filename = frame.f_code.co_filename
            self.name = frame.f_code.co_name
        else:
            self.filename = "<root>"
            self.name = ""
        self.children = []
        self.start_times = (0, 0)
        self.stop_times = (0, 0)
    def __repr__(self):
        return '%s(%r, %r, %r)' % (self.__class__.__name__, self.filename, self.name, self.children)
    def __str__(self):
        return '%s:%s' % (self.filename, self.name)

    def _sub(self, stop, start):
        if stop is None:
            return None
        if start is None:
            return None
        return stop-start

    def times(self):
        start_clock, start_time = self.start_times
        stop_clock, stop_time = self.stop_times
        return (self._sub(stop_clock, start_clock),
                self._sub(stop_time, start_time))
