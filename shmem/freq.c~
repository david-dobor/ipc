#include <stdio.h>
#include <ctype.h>
#include <string.h>
//#include <unistd.h>
#include "tnode.h"

#define MAXWORD 150
struct tnode *addtree(struct tnode *, char *);
void treeprint (struct tnode *);
int getword(char *, int); 

int main() {
    struct tnode *root;
    char word[MAXWORD];

    char *p;

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
	if (isalpha(word[0])) {
	    for( p = word; *p != '\0'; p++)
		*p = tolower(*p);
	    root = addtree(root, word);
	}
    treeprint(root);
    return 0;
}

