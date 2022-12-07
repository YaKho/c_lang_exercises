#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define strdup __strdup
#define	MAXWORD 100

struct linkline {
	int linenum;
	struct linkline *ptr;
};

struct tnode {
	char *word;
	struct linkline *lines;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *, int);
void treeprint(struct tnode *);
int getword(char *, int);
int cmpexpt(char *);

int main(int argc, char const *argv[])
{
	struct tnode *root;
	char word[MAXWORD];
	int linenum = 1;

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]) && cmpexpt(word) < 0)
			root = addtree(root, word, linenum);
		else if (word[0] == '\n')
			linenum++;
	treeprint(root);

	return 0;
}

struct tnode *talloc(void);
struct linkline *lalloc(void);
char *strdup(char *);
void addline(struct tnode *, int);

struct tnode *addtree(struct tnode *p, char *w, int linenum)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->lines = lalloc();
		p->lines->linenum = linenum;
		p->lines->ptr = NULL;
		p->left = p->right = NULL;
	} else if ((cond = strcmp(w, p->word)) == 0)
		addline(p, linenum);
	else if (cond < 0)
		p->left = addtree(p->left, w, linenum);
	else
		p->right = addtree(p->right, w, linenum);
	return p;
}

void addline(struct tnode *p, int linenum)
{
	struct linkline *tmp;

	tmp = p->lines;
	while(tmp->ptr != NULL && tmp->linenum != linenum)
		tmp = tmp->ptr;
	if (tmp->linenum != linenum) {
		tmp->ptr = lalloc();
		tmp->ptr->linenum = linenum;
		tmp->ptr->ptr = NULL;
	}
}

void treeprint(struct tnode *p)
{
	struct linkline *tmp;

	if (p != NULL) {
		treeprint(p->left);
		printf("%15s:", p->word);
		for (tmp = p->lines; tmp != NULL; tmp = tmp->ptr)
			printf("%4d", tmp->linenum);
		printf("\n");
		treeprint(p->right);
	}
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

struct linkline *lalloc(void)
{
	return (struct linkline *) malloc(sizeof(struct linkline));
}

char *strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

int cmpexpt(char *w)
{
	static char *expt[] = {
		"a", "an", "are", "in", "is", "of",
		"or", "that", "the", "this", "to"
	};
	int cond, mid;
	int low = 0;
	int high = sizeof(expt)/sizeof(char *) - 1;

	while(low <= high) {
		mid = (low + high)/2;
		if ((cond = strcmp(w, expt[mid])) < 0)
			high = mid - 1;
		else if (cond > 0)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}

int getword (char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while(isspace(c = getch()))
		if (c == '\n')
			break;
	if (c != EOF)
		*w++ = tolower(c);
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = tolower(getch()))) {
			if (*w != '\'') {
				ungetch(*w);
				break;
			}
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