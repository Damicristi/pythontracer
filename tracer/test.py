import time

def g():
    time.sleep(0.1)
    print 'g'

def h():
    print 'h'
    1/0

def f():
    for i in xrange(10):
        g()
    try:
        h()
    except:
        print "Caught h"

if __name__ == '__main__':
    f()
