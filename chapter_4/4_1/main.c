#include <stdio.h>
#define MAXLINE 1000
#define getline __getline

int getline(char line[], int max);
int strindex(char source[], char searchfor[]);

char pattern[] = "ould";

int main()
{
	char line[MAXLINE];
	int pos;
	int found = 0;
	while (getline(line, MAXLINE) > 0)
		if ((pos = strindex(line, pattern)) >= 0) {
			printf("%s\n", line);
			printf("%d\n", pos);
			found++;
		}

	return 0;
}

int getline(char s[], int lim)
{
	int c, i;
	i = 0;
	while(--lim > 0 && (c = getchar()) != EOF && c != '\n')
		s[i++] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}

int strindex(char s[], char t[])
{
	int i, j, k;
	for (i = 0; s[i] != '\0'; i++) {
		for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
			;
		if (k > 0 && t[k] == '\0')
			return i + k - 1;
	}
	return -1;
}
