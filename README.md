### Linux Interprocess Communications

This project consists of three parts. Each part performs the same task: 
given a text file, output a list showing the count of each unique word 
(case insesitive). In each part, the `parent` process creates
a `child`  process. The `parent` process opens the text file, reads the bytes, 
and passes them to the `child`. The `parent` process cannot count words; the 
`child`  process  cannot open the file, but it can count the words.

+ *Part 1* - the `pipes` directory : uses `pipe`s as the method of passing the file content.

+ *Part 2* - the `msgs` directory : uses `Message Queue`s as the method of passing the file content.

+ *Part 3* - the `shmem` directory : uses `Shared Memory` as the method of passing the file content, where the `child` process creates 4 threads, each acting as a Mapper. 
There is a separate Reducer that combines the results of the Mappers' outputs. 

Each of the directories contains its own `README` file.

##### References

+ Lecture Slides by Dr. Qiang Zeng

+ K&R, the C Programming Language.

+ [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html)

+ [Linux Interprocess Communications](http://www.tldp.org/LDP/lpg/node7.html)
