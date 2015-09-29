#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <errno.h>

#define FILE_NAME "tale.txt"
//#define FILE_NAME "tinyTale.txt"
//#define FILE_NAME "ANNA_KARENINA.txt"

void display(char *prog, char *bytes, int n);

int main(void)
{
    const char *name = "/shm-example";	// file name
    const int SIZE = 4194304;		// file size

    int shm_fd;		/* file descriptor, from shm_open()  */
    char *shm_base;     /* base address, from mmap()         */
    char *ptr;		/* shm_base is fixed, ptr is movable */
    FILE *infile;       /* pointer to a file to read         */
    int infile_size;    /* number of bytes the infile takes  */

    /* create the shared memory segment as if it was a file */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
	printf("prod: Shared memory failed: %s\n", strerror(errno));
	exit(1);
    }

    /* configure the size of the shared memory segment */
    ftruncate(shm_fd, SIZE);

    /* map the shared memory segment to the address space of the process */
    shm_base = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (shm_base == MAP_FAILED) {
	printf("prod: Map failed: %s\n", strerror(errno));
	exit(1);
    }

    display("prod", shm_base, 64);

    /* Open the infile and determine its size  */
    infile = fopen(FILE_NAME, "rt");
    fseek(infile, 0L, SEEK_END);
    infile_size = ftell(infile);
    printf("Size of file is %d \n", infile_size);
    fseek(infile, 0L, SEEK_SET);

    /* Write to the mapped shared memory region, */
    /* incrementing ptr after each write */
    for (ptr = (char *) shm_base; ptr <= shm_base+infile_size; ptr++) 
	*ptr = getc(infile);
  

    display("prod", shm_base, 64);

    /* remove the mapped memory segment from the address space of the process */
    if (munmap(shm_base, SIZE) == -1) {
	printf("prod: Unmap failed: %s\n", strerror(errno));
	exit(1);
    }

    /* close the shared memory segment as if it was a file */
    if (close(shm_fd) == -1) {
	printf("prod: Close failed: %s\n", strerror(errno));
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
