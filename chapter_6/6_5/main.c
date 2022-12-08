#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

int main(int argc, char const *argv[])
{
	install("Michael", "father");
	install("Jane", "mother");
	install("Tommy", "son");
	install("Molly", "daughter");
	install("N", "dog");
	printhashtab();

	printf("\n");
	undef("N");
	printhashtab();

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