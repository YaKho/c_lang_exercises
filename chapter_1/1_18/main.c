#include <stdio.h>

#define getline __getline
#define MAXLINE 1000 /* max size of input line */

int getline(char linef[], int lim);

/* print longest line */
main()
{
	int len; /* length current line */
	char line[MAXLINE]; /* current line */
	while ((len = getline(line, MAXLINE)) > 0) 
		if (line[0] == '\n') {
			line[0] = line[1] = 0;
		} else {
			printf("%s", line);	
		}
	return 0;
}

/* getline: read line to s, retrun length */
int getline(char s[], int lim)
{
	int c, i;
	for (i = 0; i < lim-1 && (c = getchar()) != EOF && c != '\n';) {
		if (c == ' ' || c == '\t') {
			if (i > 0) {
				if (s[i-1] != ' ')
					s[i++] = ' ';
			} else
				s[i++] = ' ';
		} else
			s[i++] = c;
	}
	if (c == '\n') {
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return i;
}
