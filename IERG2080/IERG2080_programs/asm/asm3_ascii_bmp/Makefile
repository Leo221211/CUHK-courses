src := main.c rescale.c bmp_access.c
obj := $(src:.c=.o)

t_src := test.c  rescale.c bmp_access.c
t_obj := $(t_src:.c=.o)

prog := bmp_ascii

CFLAGS = -std=gnu11

all: $(prog)

test: $(t_obj)
	$(CC) $(t_obj) -o test

debug:
	$(CC) $(obj) -o bmp_dbg -ggdb

$(prog): $(obj)
	$(CC) $(obj) -o $(prog)

.SUFFIXES: .c

.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o