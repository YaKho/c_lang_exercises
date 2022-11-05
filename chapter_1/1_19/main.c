#include <stdio.h>

#define MAXLINE 100
#define getline __getline

int getline(char[], int);
void reverse(char[]);

main()
{
	char line[MAXLINE];
	while(getline(line, MAXLINE) > 0) {
		reverse(line);
		printf("%s", line);
	}
	return 0;
}

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

void reverse(char s[])
{
	int i, cnt;
	for (cnt = 0; s[cnt] != '\0'; ++cnt)
		;
	char tmp[cnt];
	for (i = 0; (tmp[i] = s[i]) != '\0'; ++i)
		;
	for (i = 0; cnt > 0; ++i, --cnt)
		s[i] = tmp[cnt-1];
	s[i] = '\0';
}