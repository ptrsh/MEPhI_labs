CC = gcc

CFLAGS = -g -std=c11

TESTFLAGS = --leak-check=full -s

SRCS_LIST = library/stack_list.c library/list.c

SRCS_VECTOR = library/stack_vector.c library/vector.c

SRCS_STR = library/str.c

ifeq ($(struct), vector)
	SRCS = $(SRCS_VECTOR) $(SRCS_STR)
else
	SRCS = $(SRCS_LIST) $(SRCS_STR)
endif

all: Lab2

Lab2: main.c $(OBJS)
	$(CC) $(CFLAGS) $(SRCS) main.c -o main

test:
	valgrind $(TESTFLAGS) ./main

clean:
	rm -f *.o main


