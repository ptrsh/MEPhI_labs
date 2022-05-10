C = gcc

CFLAGS = -std=c11

TESTFLAGS = --leak-check=full

SRCS_VIEWS = lib/views/table_view.c lib/views/menu.c lib/views/item_view.c lib/views/errors.c

SRCS_MODELS =  lib/models/table.c lib/models/keyspace1.c lib/models/keyspace2.c lib/models/item.c  

SRCS_CONTROLLERS = lib/controllers/table_controller.c

SRCS_OTHER = lib/app.c lib/other/readline.c lib/other/common_helper.c lib/other/item_helper.c lib/other/keyspace1_helper.c lib/other/keyspace2_helper.c lib/other/table_helper.c

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