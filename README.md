### Linux Interprocess Communications

This project consists of three parts, each part exploring a different way ( of many ) 
in which processes on a Linux system can communicate. Each part performs the same task: 
given a text file, output a list showing the count of each unique word 
(case insensitive). In each part, the `parent` process creates
a `child` process. The `parent` process opens the text file, reads the bytes, 
and passes them to the `child`. The `parent` process cannot count words; the 
`child` process cannot open the file, but it can count the words.

`Message queues` and `pipes` rely on the kernel to share data among processes. Because 
of this kernel overhead, they tend to be slower than the `shared memory` way of inter-process communication. We verify this by setting the timers in each of the three programs.

**Map Reduce** refers to two separate tasks of processing (usually large amounts of)
data. The tasks are `map` and `reduce`, and are performed sequentially. The map job 
is the first task in the sequence. It takes some data as input and converts it to 
another form where individual elements are key/value pairs (tuples). There are usually 
several mappers working in *parallel* to produce this output of tuples.
The Reduce job then takes the output of the mappers and combines them to
produce a smaller output of its own. This output is also a set of key/value pairs. 
An example of this is the third part of the project where 4 mappers processed 
a quarter of a large text file. Each mapper output the words found in its chunk of the 
text, together with the frequencies with which these word occurred. The reducer then
combined these results to produce the frequencies of unique words in the original
text file.

**Hadoop** is a popular software framework for storing massive amounts of data and 
for fast concurrent processing that data. Among the many reasons for Hadoop’s popularity
are its open source nature, its massive storage capability, and its enormous 
processing power. Hadoop also offers advantages over traditional databases that require preprocessing of data before storing it; Hadoop users can store virtually limitless amounts of any kind of data and then decide how to use it later. 
An increase in demand for fast processing of any kind of data - especially from social media, the internet of things, the financial industry - coupled with Hadoop’s ability 
to store *any* kind of data, and *process it in parallel*, quickly, using clusters of
low-cost computers, is sure to contribute to Hadoop’s popularity in the  
future as well. 

 
**The Directory Structure**

+ *Part 1* - the `pipes` directory: uses `pipe`s as the method of passing the file content.

+ *Part 2* - the `msgs` directory: uses `Message Queue`s as the method of passing the file content.

+ *Part 3* - the `shmem` directory: uses `Shared Memory` as the method of passing the file content, where the `child` process creates 4 threads, each acting as a Mapper. 
There is a separate Reducer that combines the results of the Mappers' outputs. 

Each of the directories contains its own `README` file.

##### References

+ Lecture Slides by Dr. Qiang Zeng

+ K&R, the C Programming Language.

+ [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html)

+ [Linux Interprocess Communications](http://www.tldp.org/LDP/lpg/node7.html)
