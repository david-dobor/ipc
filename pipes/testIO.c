#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


//#define FILE_NAME "ANNA_KARENINA.txt"
#define FILE_NAME "tinyTale.txt"
//#define BUFSIZE 2000


int
main(int argc, char *argv[])
{
  int pipefd[2];
  pid_t cpid;
  //char buf;
  char buf[BUFSIZ];

  FILE *infile, *outfile;
  int fd_in, fd_out;
  int n;

  infile = fopen(FILE_NAME, "r");
  outfile = fopen("temp", "w");

  int c;
  while( (c = getc(infile)) != EOF ){
      putc(c, outfile);
      putc(c, stdout);
  }
  
  return 0;
}
