CC=gcc
CFLAGS=-g -O0 -mhtm -mcpu=power8

tcheck:	tcheck.o 
	gcc $(CFLAGS) -o tcheck tcheck.o

clean:
	rm -fr *.o
	rm -fr tcheck
