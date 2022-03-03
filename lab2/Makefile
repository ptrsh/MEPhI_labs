CC = gcc

CFLAGS = -g -std=c11

LDLIBS = -lreadline

TESTFLAGS = --leak-check=full -s

OBJS_LIST = stack_list.o list.o

OBJS_VECTOR = stack_vector.o vector.o

ifeq ($(struct), vector)
	OBJS = $(OBJS_VECTOR)
else
	OBJS = $(OBJS_LIST)
endif

all: Lab2

Lab2: main.c $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) main.c $(LDLIBS) -o main

test:
	valgrind $(TESTFLAGS) ./main

clean:
	rm -f *.o

list.o: library/list.c
	$(CC) -c library/list.c

stack_list.o: list.o library/stack_list.c
	$(CC) list.o -c library/stack_list.c

vector.o: library/vector.c
	$(CC) -c library/vector.c

stack_vector.o: vector.o library/stack_vector.c
	$(CC) vector.o -c library/stack_vector.c
