#include <stdio.h>
#include <string.h>

#define strend __strend
#define MAXLINE 1000 /* max size of input line */

int strend(char *s, char *t);

/* print longest line */
int main()
{
	char from[MAXLINE] = "world!";
	char to[MAXLINE] = "hello world!";
	printf("%s\n%s\n%d\n", from, to, strend(to, from));

	return 0;
}

int strend(char *s, char *t)
{
	char tmps = *s;
	char tmpt = *t;
	s = s + strlen(s);
	t = t + strlen(t);
	while(*s == *t){
		if (*s == tmps || *t == tmpt)
			break;
		s--;
		t--;
	}
	if (*s == *t && *t == tmpt && *s != '\0')
		return 1;
	else
		return 0;
}
