#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "tnode.h"

struct tnode *talloc(void);
//char *strdup(char *);

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;

    if (p == NULL) {
	p = talloc();
	p->word = strdup(w);
	p->count = 1;
	p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0)
	p->count++;
    else if (cond < 0)
	p->left = addtree(p->left, w);
    else
	p->right = addtree(p->right, w);
    return p;
}


/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
	treeprint(p->left);
	printf("%-17s : %d\n", p->word, p->count);
	treeprint(p->right);
    }
}

/* treesave: save the tree to a file */
void treesave (struct tnode *p, FILE *fp)
{
    char readbuf[80];
    if (p != NULL) {
	treesave(p->left, fp);
	sprintf(readbuf,"%s : %d\n", p->word, p->count);
	fputs(readbuf, fp);
	treesave(p->right, fp);
    }
}




/* talloc(): make a node */
struct tnode *talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}


/* char *strdup(char *s) /\* make a duplicate of s *\/ */
/* { */
/*     char *p; */

/*     p = (char *) malloc(strlen(s) + 1); /\* +1 for '\0' *\/ */
/*     if (p != NULL) */
/* 	strcpy(p, s); */
/*     return p; */
/* } */

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
