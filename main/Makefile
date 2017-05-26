CC = arm-none-linux-gnueabi-gcc

all:
	make -C ../src
	$(CC) main.c -o test_tty -L ../src/ -laplex_tty

install:all
	make -C ../src  install
	cp test_tty  ../bin -rf

clean:
	rm -rf test_tty
	make clean -C ../src

uninstall:
	make -C ../src unstall
	rm -rf ../bin/*

