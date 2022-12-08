#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define strdup __strdup

struct nlist { // element of table
	struct nlist *next; // pointer to next element
	char *name; // name
	char *defn; // text
};

struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);
void printhashtab(void);
void undef(char *name);
int getdefn(void);

int main(int argc, char const *argv[])
{
	if (getdefn())
		printhashtab();
	else
		printf("not one 'define' not found\n");

	return 0;
}

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE];

void printhashtab(void)
{
	int i;
	struct nlist *p;
	for (i = 0; i < HASHSIZE; i++) {
		p = hashtab[i];
		while (p != NULL) {
			printf("{ %02x } [%p %p] %s is %s\n",
			i, (void *) p, (void *) p->next, p->name, p->defn);
			p = p->next;
		}
	}
}

unsigned hash(char *s)
{
	unsigned hashval;

	for (hashval = 0; *s != '\0'; s++)
		hashval = *s + 31 * hashval;
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
	struct nlist *np;

	for (np = hashtab[hash(s)]; np != NULL; np = np->next)
		if (strcmp(s, np->name) == 0)
			return np; // found
	return NULL; // not found
}

char *strdup(char *);

struct nlist *install(char *name, char *defn)
{
	struct nlist *np;
	unsigned hashval;

	if ((np = lookup(name)) == NULL) { // not found
		np = (struct nlist *) malloc(sizeof(*np));
		if (np == NULL || (np->name = strdup(name)) == NULL)
			return NULL;
		hashval = hash(name);
		np->next = hashtab[hashval];
		hashtab[hashval] = np;
	} else // already there
		free((void *) np->defn);
	if ((np->defn = strdup(defn)) == NULL)
		return NULL;
	return np;
}

void undef(char *name)
{
	if ((lookup(name)) == NULL)
		return;

	struct nlist *np, *prev;
	unsigned hashval = hash(name);

	for (np = hashtab[hashval], prev = NULL; np != NULL;
		 prev = np, np = np->next) {
		if (strcmp(np->name, name) == 0) {
			free(np->name);
			free(np->defn);
			if (prev == NULL)
				hashtab[hashval] = np->next;
			else
				prev->next = np->next;
			free(np);
			return;
		}
	}
}

char *strdup(char *s)
{
	char *p;
	p = (char *) malloc(strlen(s)+1);
	if (p != NULL)
		strcpy(p, s);
	return p;
}

#define MAXWORD 100
int getword (char *word, int lim);

int getdefn()
{
	int n, i = 0;
	char buf[MAXWORD];
	char vbuf[MAXWORD];

	while ((n = getword(buf, MAXWORD) != EOF)) {
		if (strcmp(buf, "#define") == 0) {
			if ((n = getword(buf, MAXWORD)) != EOF) {
				if (isalpha(buf[0])){
					if ((n = getword(vbuf, MAXWORD)) != EOF) {
						if (vbuf[0] == '\n')
							install(buf, " ");
						else
							install(buf, vbuf);
						i++;
					}
				}
			}
		}
	}
	return i;
}

int getword (char *word, int lim)
{
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while(isspace(c = getch()) && c != '\n')
		;
	if (c != EOF)
		*w++ = c;
	if (c == '/')
		if ((c = getch()) == '/') {
			while((c = getch()) != '\n')
				;
			*w = '\0';
			return word[0];
		} else if (c == '*') {
			while((*w = getch()) != '/' && *(w-1) != '*')
				w++;
			*w = '\0';
			return word[0];
		}
	if (!isalnum(c) && c != '\'' && c != '\"' && c != '#' && c != '_') {
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
