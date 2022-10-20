CC = g++

CFLAGS = -g -std=c++17

VALGRINDFLAGS = --leak-check=full

GTESTFLAGS = -lgtest -lgmock -pthread

SRCS = lib/app.cpp lib/nephroid.cpp

all: build 

build: main.cpp
	$(CC) $(CFLAGS) $(SRCS) main.cpp -o main

run:
	./main	

valgrind:
	valgrind $(VALGRINDFLAGS) ./main

clang-analyzer:
	scan-build -analyze-headers $(CC) $(CFLAGS) $(SRCS) main.cpp -o main

test:
	$(CC) $(CFLAGS) $(SRCS) tests/testing.cpp -o test $(GTESTFLAGS) && ./test

clean:
	rm -f main test