C = gcc

CFLAGS = -std=c99

TESTFLAGS = --leak-check=full

SRCS_VIEWS = lib/views/tree_view.c lib/views/dialog.c 

SRCS_MODELS =  lib/models/node.c 

SRCS_CONTROLLERS = lib/controllers/tree_controller.c

SRCS_OTHER = lib/app.c lib/other/readline.c

SRCS = $(SRCS_VIEWS) $(SRCS_MODELS) $(SRCS_CONTROLLERS) $(SRCS_OTHER)

OBJS = $(SRCS: .c=.o)

all: build 

build: main.c 
	$(CC) $(CFLAGS) $(SRCS) main.c -o main

run:
	./main	

test:
	valgrind $(TESTFLAGS) ./main

clean:
	rm -f main