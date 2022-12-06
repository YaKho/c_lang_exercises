#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define qsort __qsort
#define getline __getline
#define MAXLINES 100

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int order,
	int (*comp) (void *, void *));
int numcmp(char *, char *);
int regcmp(char *, char *);

int main(int argc, char const *argv[])
{
	int nlines, c;
	int numeric = 0;
	int order = 1;
	int reg = 0;

	int (*func)(void *, void *);
	
	while (--argc > 0 && (*++argv)[0] == '-')
		while(c = *++argv[0])
			switch(c) {
			case 'n':
				numeric = 1;
				break;
			case 'r':
				order = -1;
				break;
			case 'f':
				reg = 1;
				break;
			default:
				printf("error: wrong key\n");
				return 1;
			}
	if (argc) {
		printf("error: too many args\n");
		return 1;
	}

	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		if (numeric)
			func = (int (*)(void *, void *)) numcmp;
		else if (reg)
			func = (int (*)(void *, void *)) regcmp;
		else
			func = (int (*)(void *, void *)) strcmp;
		qsort((void **) lineptr, 0, nlines-1, order, func);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("Entered too much lines\n");
		return 1;
	}
}

void qsort(void *v[], int left, int right, int order,
	int (*comp) (void *, void *))
{
	int i, last;
	void swap(void *v[], int, int);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (order * (*comp) (v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1, order, comp);
	qsort(v, last+1, right, order, comp);
}

int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2)
		return -1;
	else if (v1 > v2)
		return 1;
	else
		return 0;
}

int regcmp(char *s1, char *s2)
{
	while (tolower(*s1) == tolower(*s2) && *s1 != '\0' && *s2 != '\0')
		s2++, s1++;
	if (*s1 == '\0' && *s2 == '\0')
		return 0;
	else
		return tolower(*s1) - tolower(*s2);
}

void swap(void *v[], int i, int j)
{
	void *temp;
	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

#define MAXLEN 100

int getline(char *, int);

char line[MAXLEN];

int readlines(char *lineptr[], int maxlines)
{
	char *buf;
	int c, lcnt = 0;
	while ((c = getline(line, MAXLEN)) > 0) {
		if (lcnt == maxlines)
			break;
		buf = malloc(c + 1);
		lineptr[lcnt++] = strcpy(buf, line);
	}
	return lcnt;
}

void writelines(char *lineptr[], int nlines)
{
	int tmp = nlines;
	printf("All of %d lines:\n", nlines);
	while(nlines) {
		printf("[%d] : %s", tmp - nlines, lineptr[tmp - nlines]);
		nlines--;
	}
}

int getline(char s[], int maxlen)
{
	int i, c;
	for (i = 0; i < maxlen-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';

	return i;
}