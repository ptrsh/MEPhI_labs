AS = /usr/bin/nasm
LD = /usr/bin/ld

ASFLAGS = -g -f elf64
LDFLAGS = -static

SRCS = lab.s
OBJS = $(SRCS:.s=.o)

EXE = lab

SORT_ORDER = ASC

ifdef DESC
SORT_ORDER = DESC
endif

all: $(SRCS) $(EXE)

clean:
	rm -rf $(EXE) $(OBJS)

$(EXE): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $@

.s.o:
	$(AS) $(ASFLAGS) -D SORT_ORDER=$(SORT_ORDER) $< -o $@

# run 'make' to sort in asc order
# run 'make DESC=1' to sort in desc order