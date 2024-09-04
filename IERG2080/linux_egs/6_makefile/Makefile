src := main.c fn1.c
obj := $(src: .c=.o)
prog := mfprog
CFLAGS = -O3 -Wall

all: $(prog)

$(prog): $(obj)
	$(CC) $(obj) -o $(prog)

.SUFFIXES: .c
.c.o:
	$(CC) $(CFLAGS) -c $<

clean:
	$(RM) *.o