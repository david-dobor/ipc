#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define FILE_NAME "ANNA_KARENINA.txt"
//#define FILE_NAME "tinyTale.txt"

int main()
{
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
}
