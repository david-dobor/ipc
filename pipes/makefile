CC=gcc
CFLAGS=-I.
OPT = -std=c99 -Wall -Wextra

freq: freq.o tree.o getword.o
	$(CC) $(OPT) -o freq freq.o tree.o getword.o -I.

pipe: pipe.c
	gcc $(OPT) -o pipe pipe.c $(LIB)

run: pipe freq
	./pipe
	./freq

all: pipe freq

clean:
	rm -f pipe freq *.o *.*~ *~
