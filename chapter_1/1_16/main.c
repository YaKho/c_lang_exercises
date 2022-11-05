#include <stdio.h>

#define getline __getline
#define MAXLINE 1000 /* max size of input line */

int getline(char linef[], int lim);
void copy(char to[], char fromf[]);

/* print longest line */
main()
{
	int len; /* length current line */
	int max; /* length lonest line */
	char line[MAXLINE]; /* current line */
	char longest[MAXLINE]; /* longest line */
	max = 0;
	while ((len = getline(line, MAXLINE)) > 0)
		if (len > max) {
			max = len;
			copy(longest, line);
		}
	if (max > 0) /* was there even one line? */
		printf("length: %d, line: %s", max, longest);
	return 0;
}

/* getline: read line to s, retrun length */
int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}

/* copy: copy from 'from' to 'to'; to is big enoght */
void copy(char to[], char from[])
{
	int i;
	i = 0;
	while ((to[i] = from[i]) != '\0')
		++i;
}
