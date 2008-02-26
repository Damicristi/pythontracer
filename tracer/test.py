import time

def g():
    time.sleep(0.1)
    print 'g'

def f():
    for i in xrange(10):
        g()

if __name__ == '__main__':
    f()
