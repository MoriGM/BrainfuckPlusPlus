PROG=./brainfuck++
OBJS=brainfuck++.o brainfuck++_functions.o
CC=gcc
CFLAGS=-Wall -O3

debug: ${PROG}
debug: CFLAGS=-Wall -O3 -g

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^
	
%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@

.PHONY: clean

clean:
	rm -f ${OBJS}
	rm -f ${PROG}

