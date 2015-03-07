CC = ../ucc/bin/ucc

all: 2048ucc 2048gcc

2048ucc: my2048.c
	$(CC) -o 2048ucc my2048.c

2048gcc: my2048.c
	gcc -o 2048gcc my2048.c

clean:
	rm ./2048ucc ./2048gcc
