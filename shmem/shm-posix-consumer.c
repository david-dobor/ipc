#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define kMaxLineLength		200

/* returns the length of the word read (includes whitespaces preceeding the word */
// int ReadWord( char *);

/* read til the newline character */
int ReadLine( char *line, char *cPtr );


/* this just displays the byte content (in hex). just used in testing  */
void display(char *prog, char *bytes, int n);

/*getline: readaline, return length */
//int getline(char *line, int max, FILE *fp);

int main(void)
{
    const char *name = "/shm-example";	// file name
    const int SIZE = 4194304;		// file size

    int shm_fd;		// file descriptor, from shm_open()
    char *shm_base;	// base address, from mmap()

    /* open the shared memory segment as if it was a file */
    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1) {
	printf("cons: Shared memory failed: %s\n", strerror(errno));
	exit(1);
    }

    /* map the shared memory segment to the address space of the process */
    shm_base = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
	printf("cons: Map failed: %s\n", strerror(errno));
	// close and unlink?
	exit(1);
    }

    /* read from the mapped shared memory segment */
    display("cons", shm_base, 64);	
    //printf("%s", shm_base);


    char *ptr;
    //int sz = 1985015;
    ptr = shm_base;
    printf("The value of pointer is %d\n", (int)ptr);

    printf("======== START WHILE =========\n\n");
    
    char line[ kMaxLineLength+1 ];  // room for kMaxLineLength chars + one NUL
    int n;
    int i = 1;
    while (i <= 10) {
	n = ReadLine( line, ptr);
	printf("The number of chars read in: %d\n", n );
	printf("%s\n",line );
	printf("The value of pointer is %d\n", (int)ptr);
	//n = ReadLine( line, ptr);
	printf("\n======== END ITERATION =========\n");
	ptr += strlen(line) + 1;
	i++;
    }
    

    
    
    /* FILE *out2fp; */
    /* out2fp = fopen("out2.txt", "w"); */
    /* ptr = (char *) (shm_base + file_bytes); */
    /* for (; ptr <= shm_base + 280; ptr++)  */
    /* 	putc(*ptr, out2fp); */
    /* //putc('\n', out2fp);  */


   
    /* remove the mapped shared memory segment from the address space of the process */
    if (munmap(shm_base, SIZE) == -1) {
	printf("cons: Unmap failed: %s\n", strerror(errno));
	exit(1);
    }

    /* close the shared memory segment as if it was a file */
    if (close(shm_fd) == -1) {
	printf("cons: Close failed: %s\n", strerror(errno));
	exit(1);
    }

    /* remove the shared memory segment from the file system */
    if (shm_unlink(name) == -1) {
	printf("cons: Error removing %s: %s\n", name, strerror(errno));
	exit(1);
    }

    return 0;
}

void display(char *prog, char *bytes, int n)
{
    printf("display: %s\n", prog);
    for (int i = 0; i < n; i++)
    { printf("%02x%c", bytes[i], ((i+1)%16) ? ' ' : '\n'); }
    printf("\n");
}


/* Reads bytes until the newline character, or maxlength, or EOF */
int ReadLine( char *line, char *ptr )
{
    int numCharsRead = 0;
    char c;

    while (isspace(c = *ptr)) {ptr++; ++numCharsRead;}
    //if (c != EOF) *line++ = c;

    while ( (c = *ptr) != EOF && c != '\n' && ++numCharsRead <= kMaxLineLength ) {
	//if (!isalpha(c)) { *line = '\0'; return numCharsRead;}
        *line++ = c;
	//putchar(c);
	ptr++;
    }
    
    *line = '\0';
    return numCharsRead;
}
