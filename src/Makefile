CC = arm-none-linux-gnueabi-gcc
AR = arm-none-linux-gnueabi-ar


all:
	$(CC)  aplex_tty.c   -fPIC -shared -o libaplex_tty.so
	$(CC)  -c aplex_tty.c -o libaplex_tty.o -I ../include
	$(AR)  rcv libaplex_tty.a libaplex_tty.o

install:all
	cp *.so   ../lib -rf

clean:
	rm *.so *.o *.a

unstall:
	rm  -rf  ../lib/*.so
