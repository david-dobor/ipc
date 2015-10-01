#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 40

int main() {
    struct tnode *root;

    FILE *in1= fopen("FREQ1", "r");
    FILE *in2= fopen("FREQ2", "r");
    FILE *outR = fopen("OUTR", "w");
       
    const char sep[2] = ":";  //word from freq seperator
    char *word;
    char *freqStr;
    int   freqNum;
   
    char *line; int nbytes = 60; int bytes_read;
    line = (char *) malloc (nbytes + 1);
    
//    bytes_read = getline (&line, (size_t *)&nbytes, in1);


   /*  char temp[2]; */
   /*  while ( fscanf(in1," %s ", line ) != EOF )  */
   /* { */
   /*     word = strtok(line, sep); */
   /*     //freqStr = strtok(NULL, sep); */
   /*     sscanf(line, "%s", &temp[0]);   //SEGFAULT */
   /*     sscanf(line, "%d", &freqNum); */
   
   /*     printf("%s %d\n", word, freqNum); */
   /* } */


    while(1) {
	fgets(line, 80, in1);
	if(feof(in1)) break;
	word = strtok(line, sep);
	freqStr  = strtok(NULL, sep);
        freqNum = atoi(freqStr);
	printf ("%s \t", word); 
	printf ("%d\n", freqNum); 
//	fputs(line, stdout);
    }

    
    /* get the first token */
    
    /* get second token, and convert it to number */
 

    
   
    /* /\* These 2 lines are the heart of the program. *\/ */

    /* puts ("The first word in line is:"); */
    /* puts (word); */
    /* printf ("The first Number is: %d\n", freqNum); */


    fclose(in1); fclose(in2); fclose(outR);
}
