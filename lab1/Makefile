CC = gcc

CFLAGS = -std=c11

LDFLAGS = -lm -lreadline

TESTFLAGS = --leak-check=full -s

all: Lab1

Lab1: lab1.c
	$(CC) -g lab1.c $(CFLAGS) $(LDFLAGS) -o lab1

test:
	valgrind $(TESTFLAGS) ./lab1

clean:
	rm -f lab1
