### Using *Message Queue*s to Pass the File Content 

**//TO DO** This part should be relatively straightforward - **Do This Last**

+ Process 1 will create and connect to the queue using `msgget(key_t key, int msgflg)`

+ Process 1 will start sending *fixed length* messages to the queue using `msgsnd()`.

+ Process 2 will connect to the queue and start receiving messages using `msgrcv()`


##### References

+ [Beej's Guide to Unix IPC](http://beej.us/guide/bgipc/output/html/singlepage/bgipc.html)

+ [Linux Interprocess Communications](http://www.tldp.org/LDP/lpg/node7.html)

