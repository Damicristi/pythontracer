CC=gcc -fPIC -g -Wall -c -I/usr/include/python2.5
LD=gcc -shared -g
PYREXC=pyrexc

tracer.so: ../graphfile/graphfile.o tracer.o
	$(LD) -o $@ $^

tracer.o: tracer.c ../graphfile/graphfile.h
	$(CC) -o $@ $<

tracer.c: tracer.pyx
	$(PYREXC) -o $@ $<

.PHONY: clean

clean:
	-rm *.o *.so