CC = g++

CFLAGS = -g -std=c++17

TESTFLAGS = --leak-check=full

SRCS = lib/matrix.cpp lib/utils.cpp

all: build 

build: main.cpp
	$(CC) $(CFLAGS) $(SRCS) main.cpp -o main

run:
	./main	

valgrind:
	valgrind $(TESTFLAGS) ./main

clang-analyzer:
	scan-build -analyze-headers $(CC) $(CFLAGS) $(SRCS) main.cpp -o main

clean:
	rm -f main