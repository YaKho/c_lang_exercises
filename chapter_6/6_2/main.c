#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define strdup __strdup
#define	MAXWORD 100

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);

int main(int argc, char const *argv[])
{
	int first = 6;
	if (argc > 1)
		if (isdigit((*(argv+1))[0]))
			first = atoi(argv[1]);
		else {
			printf("error: argv[1] must be digit\n");
			return -1;
		}

	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && strlen(word) > first)
			root = addtree(root, word, first);
	treeprint(root);

	return 0;
}

struct tnode *talloc(void);
char *strdup(char *, int num);

struct tnode *addtree(struct tnode *p, char *w, int num)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w, num);
		p->count = 1;
		p->left = p->right = NULL;
	} else if ((cond = strncmp(w, p->word, num)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w, num);
	else
		p->right = addtree(p->right, w, num);
	return p;
}

void treeprint(struct tnode *p)
{
	if (p != NULL) {
		treeprint(p->left);
		printf("%4d %s\n", p->count, p->word);
		treeprint(p->right);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s, int num)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL) {
		*p = '\0';
		//strncpy(p, s, num);
		strncat(p, s, num);
	}
	return p;
}

int getword (char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while(isspace(c = getch()))
		;
	if (c != EOF)
		*w++ = c;
	if (c == '/')
		if ((c = getch()) == '/') {    // do auto 
			while((c = getch()) != '\n')
				;
			*w = '\0';
			return word[0];
		} else if (c == '*') { /* signed register */
			while((*w = getch()) != '/' && *(w-1) != '*')
				w++;
			*w = '\0';
			return word[0];
		}
	if (!isalpha(c) && c != '\'' && c != '\"') {
		*w = '\0';
		return c;
	}
	if (c == '\'' || c == '\"') {
		while((*w = getch()) != '\'' && *w != '\"')
			w++;
		*w = '\0';
		return word[0];
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch()) && *w != '_') {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}

#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void) {
  	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) {
  	if (bufp >= BUFSIZE)
    	printf("ungetch: too many characters\n");
  	else
    	buf[bufp++] = c;
}