#include <stdio.h>
#include <ctype.h>

/* #define BUFSIZE 100 */
/* static char buf[BUFSIZE]; /\* buffer for ungetch *\/ */
/* static int bufp=0;        /\* next free position in buf *\/ */

/* int getch(void) { */
/*     return (bufp > 0) ? buf[--bufp] : getchar(); */
/* } */


/* void ungetch(int c){ */
/*    if (bufp >= BUFSIZE) */
/*        printf("ungetch: too many characters\n"); */
/*    else */
/*        buf[bufp++] =c; */
/* } */
  

/* getword(): get the next word or character for input */
int getword(char *word, int lim, FILE *fp)
{
    int c;    //, getch(void);
    //void ungetch(int);
    char *w = word;
    while (isspace(c = getc(fp)))
	;
    if (c != EOF)
	*w++ = c;
    if (!isalpha(c)) {
	*w= '\0';
	return c;
    }
    for( ; --lim > 0; w++)
	if(!isalnum( *w = getc(fp))) {
	    ungetc(*w, fp);
	    break;
	}
    *w = '\0';
    return word[0];
}













