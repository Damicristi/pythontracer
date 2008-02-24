CC=gcc -fPIC -g -Wall -c -I/usr/include/python2.5
LD=gcc -shared -g
PYREXC=pyrexc

pygraphfile.so: ../graphfile.o pygraphfile.o
	$(LD) -o $@ $^

pygraphfile.o: pygraphfile.c ../graphfile.h
	$(CC) -o $@ $<

pygraphfile.c: pygraphfile.pyx
	$(PYREXC) -o $@ $<

.PHONY: clean

clean:
	-rm *.o *.so