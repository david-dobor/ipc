#### Using `pipe` as the Method for Passing the File Content

This directory contains the following:

1.  `freq.c` (the `child` process):

    + *input:*    some text 
    + *output:*   a list of each unique word in the text, case insensitive, together with its count. 


    For example, typing the following at a linux prompt:

    ```
    $ ./freq
    Can you can a can
    ^D
    ``` 

    will produce the following output:
    
    ```
    a                 : 1
    can               : 3
    you               : 1
    ```

    `freq` can also take a text file from standard input:
     ```
     $ ./freq < tinyTale.txt
     $ ./freq < ANNA_KARENINA.txt | head
     ```


2.  `pipe.c` (the `parent` process): 

    `pipe.c` reads an input text file (e.g. `ANNA_KARENINA.txt` ) and passes it to 
    the chid process which, in turn, counts the frequency of each word. 

3. The other `*.c` programs implement helper functions such as `getword()` that 
   gets the next word from the text file, or `printtree()` that outputs the key-value
   pairs to the standard output.
   
4. Various `*.txt` files in this directory can be used to test the programs. 

#### A Quick Note on the Data Structure Used 

We choose to place the words and their counts in a binary search tree, where the 
keys are the words and the values are their counts; we maintain the keys in order.
 (Although this is not necessary: 
 a simple hash-table with its (expected) constant time `search insert` and `delete`
 operations would have sufficed.) 
   
   
#### Compilation

The programs were tested on Linux (Debian jessie) and Mac OS X.

Here is the makefile:
```
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

```
##### References
+ Lecture Slides by Dr. Qiang Zeng.
+ K&R, the C Programming Language.
