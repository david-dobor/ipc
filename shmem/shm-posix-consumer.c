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

#define MAXLINE  120

struct tnode *addtree(struct tnode *, char *);
void treeprint (struct tnode *);


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

    char *ptr;
    //int sz = 1985015;
    ptr = shm_base;

    printf("======== START PROCESSING SHARED MEMORY =========\n\n");
    char line[MAXLINE + 1];  // room for MAXLINE chars + one NUL
    struct tnode *root;
    const char s[2] = " ";
    char *token;
    root = NULL;
    
    printf("ptr: %p \n",  ptr);
    printf("shm_base: %p \n",  shm_base);
    
    printf("======== Process the First Set of Bytes =========\n\n");
    
    while (ptr < shm_base + 141) {
	ReadLine(line, ptr);  
	ptr += strlen(line) + 1;
	printf("%s\t length: %lu\n",line, strlen(line));

	token = strtok(line, s); 	/* get the first token */
	                                /* walk through other tokens */
	while( token != NULL )  
	{ 
	    //printf( " %s\n", token );
	    root = addtree(root, token);
	    token = strtok(NULL, s); 
	} 
    }
    printf("============= Print I Part Frequencies ==============\n\n");
    treeprint(root);

    printf("\nptr now at position: %p \n\n", ptr);

    root = NULL;
    printf("======== Process the Next Set of Bytes =========\n\n");
    while (ptr < shm_base + 281) {
    	ReadLine(line, ptr);
    	ptr += strlen(line) + 1;
    	printf("%s\t length: %lu\n",line, strlen(line));
	token = strtok(line, s); 	/* get the first token */
	                                /* walk through other tokens */
	while( token != NULL )  
	{ 
	    //printf( " %s\n", token );
	    root = addtree(root, token);
	    token = strtok(NULL, s); 
	} 
    }
     printf("============= Print II Part Frequencies ==============\n\n");
     treeprint(root);

printf("\nptr now at position: %p \n", ptr);

   
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

    while ( (c = *ptr) != EOF && c != '\n' && ++numCharsRead <= MAXLINE ) {
	//if (!isalpha(c)) { *line = '\0'; return numCharsRead;}
        *line++ = c;
	//putchar(c);
	ptr++;
    }
    
    *line = '\0';
    return numCharsRead;
}
