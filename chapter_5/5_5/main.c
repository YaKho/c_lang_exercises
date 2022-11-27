#include <stdio.h>
#include <string.h>

#define strncpy __strncpy
#define strncat __strncat
#define strncmp __strncmp
#define MAXLINE 1000 /* max size of input line */

void strncpy(char *t, char *s, int n);
void strncat(char *t, char *s, int n);
int strncmp(char *t, char *s, int n);

/* print longest line */
int main()
{
	char from[MAXLINE] = "hello world!";
	char to[MAXLINE];
	strncpy(from, to, 6);
	printf("%s\nstrncpy: %s\n", from, to);
	strncat(from, to, 4);
	printf("strncat: %s\n", to);
	printf("strncmp 1: %d\n", strncmp(from, to, 5));
	printf("strncmp 2: %d\n", strncmp(from, to, 7));

	return 0;
}

void strncpy(char *t, char *s, int n)
{
	while((*s++ = *t++) && n--)
		;
	*--s = '\0';
}

void strncat(char *t, char *s, int n)
{
	s += strlen(s);
	while((*s++ = *t++) && n--)
		;
	*--s = '\0';
}

int strncmp(char *t, char *s, int n)
{
	while(*t != '\0' && (*s++ == *t++) && n--)
		;
	if (++n)
		return 0;
	else
		return 1;
}