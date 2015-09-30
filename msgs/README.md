### Using *Message Queue*s to Pass the File Content 

`parent.c`:

+ `parent.c` creates the queue and connects to the queue using `msgget(key_t key, int msgflg)`

+ `parent.c` starts sending *fixed length* messages to the queue using `msgsnd()`.

`child.c`

+ `child.c` connects to the queue and starts receiving messages using `msgrcv()`
+ `child.c` then processes the messages as before, counting the word frequencies.

Additional details can be found in the code comments.

##### References

+ [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html)

+ [Linux Interprocess Communications](http://www.tldp.org/LDP/lpg/node7.html)

