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

    `freq` can also take a text file from standard input (e.g.
     ```
     $ ./freq < tinyTale.txt
     $ ./freq < ANNA_KARENINA.txt | head
     ```).


2.  `pipe.c` (the `parent` process): 

    `pipe.c` reads an input text file (e.g. `ANNA_KARENINA.txt` ) and passes it to 
    the chid process which, in turn, counts the frequency of each word. The logic of
    this program is as follows (ignoring timing its execution and other details): 
    
    ```
    FILE *infile, *pipe_fp;
    char readbuf[80];

    infile = fopen(FILE_NAME, "rt");
    pipe_fp = popen("./freq", "w");
    while(true) {
	     fgets(readbuf, 80, infile);
	     if(feof(infile)) break;
	     fputs(readbuf, pipe_fp);
    }

    fclose(infile);
    pclose(pipe_fp);

    ```

3. The other `*.c` programs implement helper functions such as `getword()` that 
   gets the next word from the text file, or `printtree()` that outputs the key-value
   pairs to the standard output.
   
4. Various `*.txt` files in this directory can be used to test the programs. 

#### Miscellanea

* *A quick note on the data structure used.* 
  We choose to place the words and their counts in a binary search
  tree, where the keys are the words and the values are their counts.
  We find this convinient because, for example, an in-order traversal
  of this tree will output the words and their counts in alphabetical
  order. (This is not necessary, however. A simple hash-table with its 
  (expected) constant time `search insert` and `delete` operations would 
  do just fine.) 

* *What constitutes a word.*
 In this part we also implement the `getword` function, which we re-use in
 other parts. `getword` fetches the next word from the input text stream, 
 where a word is either a string of letters and digits beginning with a letter, 
 or a single non-white space character. 
   
#### Compilation

The programs were tested on Linux (Debian jessie) and Mac OS X.

Here is the makefile:
```
CC=gcc
CFLAGS=-I.
OPT = -std=c99 -Wall -Wextra

freq: freq.o tree.o getword.o
    $(CC) $(OPT) -o freq freq.o tree.o getword.o $(CFLAGS)

pipe: pipe.c
	gcc $(OPT) -o pipe pipe.c 

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
