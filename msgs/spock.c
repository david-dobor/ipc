/*
** spock.c -- reads from a message queue
*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key = (key_t) 77;  	/* key value doesn't matter here*/


    if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
	perror("msgget");
	exit(1);
    }
	
    printf("spock: ready to receive messages, captain.\n");

    for(;;) { /* Spock never quits! */
	if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
	    perror("msgrcv");
	    exit(1);
	}
	printf("spock: \"%s\"\n", buf.mtext);
    }
    //exit(0);

    return 0;
}
