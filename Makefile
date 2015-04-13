CC=gcc
CFLAG='-g'
DEBUG=' '
INCLUDE='.'

all: a.out .c.o
a.out:
	gcc -DDATA_DEBUG -o a.out *.o


.o.c:
	${CC} ${CLAG} -I${INCLUDE} -o $@ $<





.PYTHONY: 
clean:
	-rm -f *~ a.out *.o
