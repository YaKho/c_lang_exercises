#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define getline __getline
#define MAXLEN 100
#define LINES 100

int getline(char s[], int maxlines);

int main(int argc, const char *argv[])
{
	char *buf;
	char line[MAXLEN];
	char *lineptr[LINES];
	int lineprint = 10;
	int lcnt = 0;
	int n;

	if (argc > 2) {
		printf("error: too many args\n");
		return -1;
	}
	if (argc == 2) {
		if ((*(argv + 1))[0] == '-')
			lineprint = atoi(++argv[1]);
		else {
			printf("error: use 'tail [-n]'\n");
			return -1;
		}
	}

	while ((n = getline(line, MAXLEN)) > 0) {
		buf = malloc(n + 1);
		lineptr[lcnt++] = strcpy(buf, line);
	}

	if (lineprint > lcnt)
		printf("error: the entered strings are not enough\n");
	else {
		printf("last %d lines:\n", lineprint);
		while(lineprint) {
			printf("[%d] : %s", lcnt - lineprint, lineptr[lcnt - lineprint]);
			lineprint--;
		}
	}

	return 0;
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