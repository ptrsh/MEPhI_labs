CC = gcc

CFLAGS = -g -Wall -std=c11

LDLIBS = -lm -lreadline

TESTFLAGS = --leak-check=full -s

all: Lab1

Lab1: lab1.c
	$(CC) $(CFLAGS) lab1.c $(LDLIBS) -o lab1

test:
	valgrind $(TESTFLAGS) ./lab1

clean:
	rm -f lab1
