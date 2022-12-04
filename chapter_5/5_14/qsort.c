#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define qsort __qsort
#define getline __getline
#define MAXLINES 100

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(void *lineptr[], int left, int right, int order,
	int (*comp) (void *, void *));
int numcmp(char *, char *);

int main(int argc, char const *argv[])
{
	int nlines;
	int numeric = 0;
	int order = 0;
	if (argc > 2) {
		if (strcmp(argv[1], "-n") == 0)
			numeric = 1;
		if (strcmp(argv[2], "-n") == 0)
			numeric = 1;
		if (strcmp(argv[1], "-r") == 0)
			order = 1;
		if (strcmp(argv[2], "-r") == 0)
			order = 1;
	}
	if (argc > 1) {
		if (strcmp(argv[1], "-r") == 0)
			order = 1;
		if (strcmp(argv[1], "-n") == 0)
			numeric = 1;
	}		
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		qsort((void **) lineptr, 0, nlines-1, order,
			(int (*)(void*, void*))(numeric ? numcmp : strcmp));
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
		if (order) {
			if ((*comp) (v[i], v[left]) > 0)
				swap(v, ++last, i);
		} else {
			if ((*comp) (v[i], v[left]) < 0)
				swap(v, ++last, i);
		}
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