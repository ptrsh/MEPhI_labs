C = gcc

CFLAGS = -std=c11

TESTFLAGS = --leak-check=full

SRCS_VIEWS = lib/views/table_view.c lib/views/dialog.c lib/views/item_view.c lib/views/key_view.c lib/views/keyspace_view.c

SRCS_MODELS =  lib/models/table_model.c lib/models/keyspace1.c lib/models/keyspace2.c lib/models/key.c lib/models/item.c lib/models/keyspaces.c 

SRCS_CONTROLLERS = lib/controllers/table_controller.c

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