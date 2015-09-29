#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define FILE_NAME "ANNA_KARENINA.txt"
//#define FILE_NAME "tinyTale.txt"

int main()
{
    FILE *infile, *pipe_fp;
    char readbuf[80];

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    infile = fopen(FILE_NAME, "rt");
    pipe_fp = popen("./freq", "w");
    while(true) {
	fgets(readbuf, 80, infile);
	if(feof(infile)) break;
	fputs(readbuf, pipe_fp);
    }

    fclose(infile);
    pclose(pipe_fp);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Total CPU time used: %f seconds.\n", cpu_time_used);
}
