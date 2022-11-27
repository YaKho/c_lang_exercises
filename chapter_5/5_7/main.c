#include <stdio.h>
#include <string.h>

#define getline __getline
#define MAXLINES 5000
#define BUFSIZE 5000

char *lineptr[MAXLINES];

int readlines(char *lineptr[], char *buf, int nlines);
void writelines(char *lineptr[], int nlines);
void qsort(char *lineptr[], int left, int right);

int main(void)
{
	int nlines;
	char buf[BUFSIZE];
	if ((nlines = readlines(lineptr, buf, MAXLINES)) >= 0) {
		qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	} else {
		printf("error: too many lines\n");
		return 1;
	}
}

#define MAXLEN 1000

int getline(char *, int);

int readlines(char *lineptr[], char *buf, int maxlines)
{
	int len, nlines;
	char *p = buf;
	static int bufcnt = 0;
	char line[MAXLEN];
	nlines = 0;
	while((len = getline(line, MAXLEN)) > 0)
		if (nlines >= maxlines || bufcnt >= BUFSIZE)
			return -1;
		else {
			line[len-1] = '\0';
			strcpy(p, line);
			lineptr[nlines++] = p;
			p += len;
			bufcnt += len;
		}
	return nlines;
}

void writelines(char *lineptr[], int nlines)
{
	while (nlines-- > 0)
		printf("%s\n", *lineptr++);
}

int getline(char *s, int lim)
{
	int c;
	char *tmp = s;
	for (; --lim > 0 && (c = getchar()) != EOF && c != '\n'; s++)
		*s = c;
	if (c == '\n')
		*s++ = c;
	*s = '\0';
	return s - tmp;
}

void qsort(char *v[], int left, int right)
{
	int i, last;
	void swap(char *v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right)/2);
	last = left;
	for (i = left+1; i <= right; i++)
		if (strcmp(v[i], v[left]) < 0)
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last-1);
	qsort(v, last+1, right);
}

void swap(char *v[], int i, int j)
{
	char *temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}