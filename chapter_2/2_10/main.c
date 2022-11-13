#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);
void lower(char[]);

int main()
{
	char line[MAXLINE];

	while(getline(line, MAXLINE)) {
		lower(line);
		printf("%s\n", line);
	}

	return 0;
}

int getline(char s[], int maxline)
{
	int i, c;
	for (i = 0; i < maxline && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	s[i] = '\0';

	return i;
}

void lower(char s[])
{
	int i;
	for (i = 0; s[i] != '\0'; i++)
		s[i] = (s[i] >= 'A' && s[i] <= 'Z') ? (s[i] - 'A') + 'a' : s[i];
}