#include <stdio.h>
#include <string.h>

#define strcat __strcat
#define MAXLINE 1000 /* max size of input line */

void strcat(char *s, char *t);

/* print longest line */
int main()
{
	char from[MAXLINE] = " world!";
	char to[MAXLINE] = "hello";
	strcat(to, from);
	printf("%s\n", to);

	return 0;
}

void strcat(char *s, char *t)
{
	s += strlen(s);
	while (*s++ = *t++)
		;
}
