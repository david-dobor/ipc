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

#include <pthread.h>


#define FILESIZE 1985020   	/* number of bytes in a file */
#define MAXWORD 30		/* number of `words` in a file */
struct tnode *addtree(struct tnode *, char *);
void treeprint (struct tnode *);
void treesave (struct tnode *p, FILE *fp);
int getword(char *word, int lim, FILE *fp);


pthread_mutex_t map_lock = PTHREAD_MUTEX_INITIALIZER;

/* this just displays the byte content (in hex). just used in testing  */
void display(char *prog, char *bytes, int n);

/* mapper: generate the word frequencies from input file 
 *  and store it in the output file */
void mapper (FILE *infp, FILE *freqfp);
//FILE *outfp mapper (FILE *infp);


/* a mapper that pthreads will like */
void* mapper_t(void * param);


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


    pthread_t threads[2];
    long t;
    for (t = 0; t < 2; t++) {
	pthread_mutex_lock(&map_lock);
	pthread_create(&threads[t], NULL, mapper_t, (void*) (shm_base + t*100));
	printf("\n\n%s\n\n%s","******************",  shm_base + t*100);
	pthread_mutex_unlock(&map_lock);
    }

    void* result;
    for (t = 0; t < 2; t++) {
	pthread_join(threads[t], &result);
	printf("Thread %ld returned %ld\n", t, (long) result);
    }




    /* Create the second set of bytes to manipulate */
    /* FILE *out2 =  fopen("OUT2", "w");     */
    /* for (int i = 401; i < 800; i++) */
    /* { //fprintf(out2, "%02x%c", shm_base[i], ((i+1)%16) ? ' ' : '\n'); */
    /* 	fprintf(out2, "%c", shm_base[i]);} */
    /* //fprintf(out2, "\n"); */
    /* fclose(out2); */
    
    /* /\* Map the first set of bytes *\/ */
    /* out1 = fopen("OUT2", "r"); FILE *freqp2 = fopen("FREQ2", "w"); */
    /* mapper (out2, freqp2); */
    /* fclose(out2); fclose(freqp2); */

    
   
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

void mapper (FILE *infp, FILE *freqfp)
{
    struct tnode *root;
    char word[30];

    char *p;
    root = NULL;
    while (getword(word, 30, infp) != EOF)
	if (isalpha(word[0])) {
	    for( p = word; *p != '\0'; p++)
		*p = tolower(*p);
	    root = addtree(root, word);
	}
    treeprint(root);
    treesave(root, freqfp);
    //fclose(freqfp);
}

void* mapper_t(void *param)
{
    long *base = (long *) param;
    char *shm_base = (char *) base; 
    long thread_no = (long) param;

    
    if (thread_no == 0) {
	struct tnode *root;
	char word[30];
	char *p;
	root = NULL;

	
	/* Create the first set of bytes to manipulate */
	FILE *out1 =  fopen("OUT1", "w");
	for (int i = 0; i < 400; i++) 
	{ //fprintf(out1, "%02x%c", shm_base[i], ((i+1)%16) ? ' ' : '\n');
	    fprintf(out1, "%c", shm_base[i]);//}
	    //fprintf(out1, '\n');
	}
	fclose(out1);

	/* /\* Map the first set of bytes *\/ */
	/* out1 = fopen("OUT1", "r"); FILE *freqp1 = fopen("FREQ1", "w"); */
	/* while (getword(word, 30, out1) != EOF) */
	/*     if (isalpha(word[0])) { */
	/* 	for( p = word; *p != '\0'; p++) */
	/* 	    *p = tolower(*p); */
	/* 	root = addtree(root, word); */
	/*     } */
	/* treeprint(root); */
	/* treesave(root, freqp1); */
    
	
	/* fclose(out1); fclose(freqp1); */
    }
    printf("thread number %ld\n", thread_no);
    return (void*)(thread_no + 1);
}


void display(char *prog, char *bytes, int n)
{
    printf("display: %s\n", prog);
    for (int i = 0; i < n; i++)
    { printf("%02x%c", bytes[i], ((i+1)%16) ? ' ' : '\n'); }
    printf("\n");
}

