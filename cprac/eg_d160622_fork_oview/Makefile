#CC=arm-linux-gnueabihf-gcc
#AR=arm-linux-gnueabihf-ar
SRC+=moto.c

all:
	$(CC) -c $(SRC)
	$(AR) -crv libmoto.a moto.o

clean:
	rm -r -f *.o

