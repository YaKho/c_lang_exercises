#include <stdio.h>

#define getline __getline
#define MAXLINE 1000 /* max size of input line */

int getline(char linef[], int lim);
void copy(char to[], char fromf[]);

/* print longest line */
main()
{
	int len; /* length current line */
	char line[MAXLINE]; /* current line */
	while ((len = getline(line, MAXLINE)) > 0) 
		if (len > 80)
			printf("%s", line);	
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
