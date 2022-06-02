C = gcc

CFLAGS = -std=c99 -g

TESTFLAGS = --leak-check=full

SRCS_VIEWS = lib/views/dialog.c lib/views/graph_view.c

SRCS_MODELS = lib/models/graph.c lib/models/string_vector.c lib/models/vector.c 

SRCS_CONTROLLERS = lib/controllers/graph_conroller.c

SRCS_OTHER = lib/other/readline.c lib/app.c

SRCS = $(SRCS_VIEWS) $(SRCS_MODELS) $(SRCS_CONTROLLERS) $(SRCS_OTHER)

OBJS = $(SRCS: .c=.o)

all: build 

build: main.c 
	$(CC) $(CFLAGS) $(SRCS) main.c -lm -o main

run:
	./main	

test:
	valgrind $(TESTFLAGS) ./main

clean:
	rm -f main