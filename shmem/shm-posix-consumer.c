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

#define FILESIZE 1985020   	/* number of bytes in a file */
#define WORDCOUNT 430		/* number of `words` in a file */
struct tnode *addtree(struct tnode *, char *);
void treeprint (struct tnode *);
void treesave (struct tnode *p, FILE *fp);


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
    int sz = 1985015;
    ptr = shm_base;

    //printf("======== START PROCESSING SHARED MEMORY =========\n\n");
    
    printf("ptr: %p \n",  ptr);
    printf("shm_base: %p \n",  shm_base);

    printf("===================================\n");
    printf("===================================\n");
    printf("===================================\n");

    //for (ptr = (char *) shm_base; ptr <= shm_base+sz; ptr++) 
	;

	FILE * stream;
	stream = fdopen(shm_fd, "r");
	int c;
	while ((c = fgetc (stream)) != EOF)
	    putchar (c);
	fclose (stream);


/*     char bigString[FILESIZE]; */
/*     sprintf(bigString, "%s", shm_base); */
/*     printf("%s", bigString); */

/*     /\* Start tokenizing the big string and print out the tokens *\/ */
/*     /\* Also, save em in a tree *\/ */
/*     struct tnode *root; */
/*     root = NULL; */
/*     FILE *temp; */
    


/*     const char s[2] = " "; */
/*     char *token; */
    
/*     /\* get the first token *\/ */
/*     token = strtok(bigString, s); */
/* //    root = addtree(root, "David!!!"); */
/*     root = addtree(root, token); */
    //treeprint(root);
    
    /* for(int i = 1; i <= WORDCOUNT; i++) { */
    /* 	token = strtok(NULL, s); */
    /* 	printf( "%s\n", token ); */
    /*     addtree(root, token); */
    /* } */
    /* treeprint(root); */
    /* temp = fopen("temp.out", "w"); */
    /* treesave(root, temp); */
    /* fclose(temp); */
    
    /* walk through other tokens */

    /* char *p = token; */
    /* while( token != NULL )  */
    /* { */
    /* 	token = strtok(NULL, s); */
    /* 	//printf( "%s\n", token ); */
    /* 	//p = token; */
    /* } */
    /* //treeprint(root); */

    //printf("\nptr now at position: %p \n", ptr);

   
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

