#CC=arm-linux-gnueabihf-gcc
SRC+=main.c

all:
	$(CC) -E $(SRC) -o inline.i
	$(CC) -o example $(SRC) -g

clean:
	rm -r -f *.o *.i

