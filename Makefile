CC=gcc
CFLAG='-g'
DEBUG=' '
INCLUDE='.'



all: a.out .c.o
a.out:
	${CC} -DDATA_DEBUG -o a.out *.o

test_data:
	${CC} -DMIX_DATA_DEBUG -o a.out -I. ${CFLAG} mix_op.c mix_data.c
test_op:
	${CC} -DMIX_OP_DEBUG -o a.out -I. ${CFLAG} mix_op.c mix_data.c

.o.c:
	${CC} ${CLAG} -I${INCLUDE} -o $@ $<





.PYTHONY: 
clean:
	-rm -f *~ a.out *.o \#*\#
