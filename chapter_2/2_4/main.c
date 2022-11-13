#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);
void squeeze(char[], char[]);

int main()
{
	char line[MAXLINE];
	char str[] = {'a', '0', '-', '\0'};
	while(getline(line, MAXLINE)) {
		squeeze(line, str);
		printf("%s\n", line);
	}

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

void squeeze(char s1[], char s2[])
{
	int i, j, k;
	for (i = j = 0; s1[i] != '\0'; i++) {
		for (k = 0; s2[k] != '\0' && s1[i] != s2[k]; k++)
			;
		if (s2[k] == '\0')
			s1[j++] = s1[i];
	}
	s1[j] = '\0';
}