# compiler options -- C99 with warnings
OPT_GCC = -std=c99 -Wall -Wextra -g

# compiler options and libraries for Linux, Mac OS X
ifeq ($(OSTYPE),linux)
  OPT = -D_XOPEN_SOURCE=700
  LIB = -lrt -pthread
endif
ifeq ($(OSTYPE),darwin)	# Mac OS X
  OPT = 
  LIB = 
endif
ifeq ($(OSTYPE),solaris)
  OPT = -D_XOPEN_SOURCE=600
  LIB = -lrt
endif

all: cons prod

cons: shm-posix-consumer.c
	gcc $(OPT_GCC) $(OPT) -o cons shm-posix-consumer.c tree.c $(LIB)

prod: shm-posix-producer.c
	gcc $(OPT_GCC) $(OPT) -o prod shm-posix-producer.c $(LIB)

run: cons prod
	./prod
	./cons

clean:
	rm -f cons prod *.*~ *~ *.o 
	rm -rf *.dSYM
