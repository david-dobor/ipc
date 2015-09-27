### Using *Shared Memory* to Pass the File Content 

#### The Structure

We use the `POSIX` interface to share memory between processes.
The two main programs in this part are:

1. `shm-posix-producer.c` 
    + creates the shared memory segment using `shm_open()`.
    + configures the size of the shared memory segment using `ftruncate()`.
    + uses `mmap()` to map the shared memory segment.
2. `shm-posix-consumer.c` 
    + opens the shared memory segment created by the producer using `shm_open()`.
    + maps (`mmap()`s) the shared memory segment to the address space of the process.
    + reads data from the shared memory segment.

We end both main programs by removing the mapped shared memory segment from each process' address space (and do other minor housekeeping tasks).

#### Testing the programs
1. We first use a small text file `tinyTale.txt` to test our design. The objective here 
   is simple: 
   * The producer reads the textfile and writes it to the shared memory segment, 
      byte-by-byte.
   * The consumer just outputs the file contents to the standard output.
   
2. We next split the text file into two (about equal) shared memory segment parts and
   have two separate *threads* manipulate the two parts independently. Here we have 
   each thread simply output its part of the text file a line at a time.
   
3. Finally we repeat part 2 on a larger text file 
   (`ANNA_KARENINA.txt`, size: `1985015 bytes`), this time splitting the task among 4
   different processes. These are our **mappers** in the *map-reduce* context.


#### Compilation

The programs were tested on Linux (Debian jessie) and Mac OS X.

* On linux, compile with:
```
gcc -std=c99 -D_XOPEN_SOURCE=700 -o prod shm-posix-producer.c -lrt
gcc -std=c99 -D_XOPEN_SOURCE=700 -o cons shm-posix-consumer.c -lrt
```
* On Mac OS X, omit `$(OPT)` and `$(LIB)`:
```
gcc -std=c99 -o prod shm-posix-producer.c
gcc -std=c99 -o cons shm-posix-consumer.c
```

The following makefile should work:
```
OPT_GCC = -std=c99 -Wall -Wextra

# compiler options and libraries for Linux, Mac OS X or Solaris
ifeq ($(OSTYPE),linux)
  OPT = -D_XOPEN_SOURCE=700
  LIB = -lrt
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
	gcc $(OPT_GCC) $(OPT) -o cons shm-posix-consumer.c $(LIB)

prod: shm-posix-producer.c
	gcc $(OPT_GCC) $(OPT) -o prod shm-posix-producer.c $(LIB)

run: cons prod
	./prod
	./cons

clean:
	rm -f cons prod *.*~ *~ *.o 

```
##### References
+ [stackoverflow](http://stackoverflow.com/questions/9923495/undefined-reference-shm-open-already-add-lrt-flag-here)

+ [POSIX shared memory example](http://www.cse.psu.edu/~deh25/cmpsc473/notes/OSC/Processes/shm.html)




