CFLAGS=-Wall -Wextra -Werror -pedantic -g -O0
CLIBS=-L. -I. -lcurl `pkg-config --libs json-c`
CC := clang
all: compile
compile:
	mkdir -p build
	$(CC) $(CFLAGS) -c libtg.c -o build/libtg.o
	$(CC) $(CFLAGS) build/libtg.o examples/main.c -o build/ctog $(CLIBS)
run: compile
	./build/ctog
clean:
	rm -v build/*
