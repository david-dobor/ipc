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



struct my_msgbuf {
    long mtype;
    char mtext[BUFSIZ];
};

int main(void)
{
    struct my_msgbuf buf;
    int msqid;
    key_t key;

    if ((key = ftok("kirk.c", 'B')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, 0644 | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }
    
    printf("Processing the input file:\n");
    FILE *infile, *outfile;
    int fd_in, fd_out;
    int n;

    buf.mtype = 1; /* we don't really care in this case */
    fd_in = open(FILE_NAME, O_RDONLY, 0);


    
    while((n = read(fd_in, buf.mtext, BUFSIZ)) > 0) {
	//while(fgets(buf.mtext, sizeof buf.mtext, fd_in) != EOF) {
        int len = strlen(buf.mtext);
	printf("%s\n", buf.mtext);

        /* ditch newline at end, if it exists */
        //if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

        if (msgsnd(msqid, &buf, len+1, 0) == -1) /* +1 for '\0' */
            perror("msgsnd");
    

    if (msgctl(msqid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        //exit(1);
    }
    }
    return 0;
}
