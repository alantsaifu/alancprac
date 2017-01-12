# makefile test for hello program
CC=gcc
CFLAGS=
OBJS=hello.o
all: hello
hello: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o hello
hello.o: hello.c
	$(CC) $(CFLAGS) -c hello.c -o $(OBJS)
clean:
	rm -rf hello *.o

