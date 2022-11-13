#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);
int any(char[], char[]);

int main()
{
	char line[MAXLINE];
	char str[] = {'a', '0', '-', '\0'};
	while(getline(line, MAXLINE))
		printf("%s\n%s\n%d", line, str, any(line, str));

	return 0;
}

int getline(char s[], int maxline)
{
	int i, c;

	for (i = 0; i < maxline && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = '\0';

	return i;
}

int any(char s1[], char s2[])
{
	int i, k;
	for (i = 0; s1[i] != '\0'; i++) {
		for (k = 0; s1[i] != s2[k] && s2[k] != '\0'; k++)
			;
		if (s2[k] != '\0')
			return i;
	}

	return -1;
}