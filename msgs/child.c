/*
 * child.c -- reads from a message queue
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <ctype.h>

struct tnode *addtree(struct tnode *, char *);
void treeprint (struct tnode *);
void treesave (struct tnode *p, FILE *fp);
int getword(char *, int); 

struct my_msgbuf {
    long mtype;
    char mtext[200];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key = (key_t) 77;  	/* key value doesn't matter here */


    if ((msqid = msgget(key, 0644)) == -1) { /* connect to the queue */
	perror("msgget");
	exit(1);
    }
	
    printf("child is ready to collect messages from the queue\n");

    const char s[3] = " \n";  // separator
    char *aword;            // current word is stored here
    struct tnode *root;     // words and counts stored here
    root = NULL;
    root = addtree(root, "David");

    FILE *temp = fopen("TEMP.out", "a");
    for(int i = 1;i <= 4; i++) { 

	if (msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0) == -1) {
	    perror("msgrcv");
	    exit(1);
	}
	//printf("child: \"%s\"\n", buf.mtext);
	fputs(buf.mtext, stdout);
	fputs(buf.mtext, temp);
    }
    fclose(temp);
    treeprint(root); 

//return 0;
}
