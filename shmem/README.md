### Using *Shared Memory* to Pass the File Content 

#### Preliminary Tests, Overall Structure

We use the `POSIX` interface to share memory between processes.
We initially test two main programs: the producer reads a textfile (e.g `tinyTale.txt`)
and writes it to the shared memory segment, byte-by-byte. and the consumer that connects to the shared memory and manipulates these bytes somehow (e.g. simply outputs them to `stdout`).

1. `shm-posix-producer.c` 
    + creates the shared memory segment using `shm_open()`.
    + configures the size of the shared memory segment using `ftruncate()`.
    + uses `mmap()` to map the shared memory segment.
2. `shm-posix-consumer.c` 
    + opens the shared memory segment created by the producer using `shm_open()`.
    + maps (`mmap()`s) the shared memory segment to the address space of the process.
    + reads data from the shared memory segment.

We end both main programs by removing the mapped shared memory segment from each process' address space (and do other minor housekeeping tasks).

#### Splitting the Consumer Process into parts

1. We split the text file into four (about equal) shared memory segment parts and
   have four separate *threads* manipulate the parts independently. Here we have 
   each thread simply output its part of the text file a line at a time.
   
3. We next repeat the same on a larger text file 
   (`ANNA_KARENINA.txt`, size: `1985015 bytes`), again splitting the task among 4
   different threads. These are our **mappers** in the *map-reduce* context.


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
# compiler options -- C99 with warnings
OPT_GCC = -std=c99 -Wall -Wextra

# compiler options and libraries for Linux, Mac OS X
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
	gcc $(OPT_GCC) $(OPT) -o cons shm-posix-consumer.c tree.c $(LIB)

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




