PROG=./brainfuck++
OBJS=brainfuck++.o brainfuck++_functions.o
CC=gcc
CFLAGS=-Wall -O3

${PROG}: ${OBJS}
	${CC} ${CFLAGS} -o $@ $^
	
%.o: %.c
	${CC} ${CFLAGS} -c $^ -o $@
	
