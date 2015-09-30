#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <fcntl.h>

//#define FILE_NAME "ANNA_KARENINA.txt"
#define FILE_NAME "tinyTale.txt"
//#define FILE_NAME "tale.txt"
#define MSGSIZE  80


struct my_msgbuf {
    long mtype;
    char mtext[MSGSIZE];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key = (key_t) 77;  	/* key value doesn't matter here */

    if ((msqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    buf.mtype = 1; /* Any value. We set this to a positive value so */
		   /* the reciever gets the next message in queue of */
		   /* the same message type */

    /* Determine the size of the input file */
    FILE *infile;
    infile = fopen(FILE_NAME, "rt");
    fseek(infile, 0L, SEEK_END);
    int nbytes = ftell(infile);   //
    printf("Size of file is %d \n", nbytes);
    fseek(infile, 0L, SEEK_SET);

    /* Determine the number of chunks we'll put on the queue */ 
    int nchunks = nbytes / MSGSIZE  ;
    printf("Number of Message Chunks %d \n", nchunks);

    /* put the chunks on the queue */

    char c;
    while ((c = getc(infile)) != EOF) {
	ungetc(c, infile);
	for (int n = 1; n <= nchunks+1; n++) {
	    int len;
	    for(int i = 0; i < MSGSIZE; i++) {
		c = getc(infile);
		buf.mtext[i] = c;
		buf.mtext[MSGSIZE-1] = 0;
	    }
	    ungetc(c, infile); 
	    //if (buf.mtext[MSGSIZE-1] == '\n') buf.mtext[MSGSIZE-1] = '\0';
	    len = strlen(buf.mtext);
            if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
	    if (msgsnd(msqid, &buf, len+1, 0) == -1)  perror("msgsnd");
//	    printf("THE TEXT READ: %s\n", buf.mtext);
    	    printf("%s", buf.mtext);
	}

    }
//    if (msgctl(msqid, IPC_RMID, NULL) == -1) { perror("msgctl"); exit(1); }
    fclose(infile);

    return 0;
}
