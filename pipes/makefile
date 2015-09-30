CC=gcc
CFLAGS=-I.
OPT = -std=c99 -Wall -Wextra -g

freq: freq.c tree.c
	$(CC) $(OPT) -o freq freq.c tree.c $(CFLAGS)

pipe: pipe.c
	gcc $(OPT) -o pipe pipe.c $(CFLAGS)

run: pipe freq
	./pipe
	./freq

all: pipe freq

clean:
	rm -f pipe freq *.o *.*~ *~
