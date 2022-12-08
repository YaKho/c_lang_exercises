#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define strdup __strdup
#define	MAXWORD 100
#define MAXWORDS 10000

struct tnode {
	char *word;
	int count;
	struct tnode *left;
	struct tnode *right;
};

struct tnode *tnodes[MAXWORDS] = { 0 };
int tncnt = 0;

struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *p[], int n);
int getword(char *, int);
void qsortnode(struct tnode *p[], int left, int right);

int main(int argc, char const *argv[])
{
	struct tnode *root;
	char word[MAXWORD];

	root = NULL;
	while (getword(word, MAXWORD) != EOF)
		if (isalpha(word[0]))
			root = addtree(root, word);
	qsortnode(tnodes, 0, tncnt - 1);
	treeprint(tnodes, tncnt);

	return 0;
}

struct tnode *talloc(void);
char *strdup(char *);
void addline(struct tnode *, int);

struct tnode *addtree(struct tnode *p, char *w)
{
	int cond;
	if (p == NULL) {
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
		tnodes[tncnt++] = p;
	} else if ((cond = strcmp(w, p->word)) == 0)
		p->count++;
	else if (cond < 0)
		p->left = addtree(p->left, w);
	else
		p->right = addtree(p->right, w);
	return p;
}

void qsortnode(struct tnode *p[], int left, int right)
{
	int i, last;
	void swap(struct tnode *v[], int, int);
	if (left >= right)
		return;
	swap(p, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (p[left]->count > p[i]->count)
			swap(p, ++last, i);
	swap(p, left, last);
	qsortnode(p, left, last-1);
	qsortnode(p, last+1, right);
}

void swap(struct tnode *v[], int i, int j)
{
	struct tnode *temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

void treeprint(struct tnode *p[], int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%4d : %.15s\n", p[i]->count, p[i]->word);
}

struct tnode *talloc(void)
{
	return (struct tnode *) malloc(sizeof(struct tnode));
}

char *strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
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