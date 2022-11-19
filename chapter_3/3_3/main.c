#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);
void expand(char[], char[]);

int main()
{
	char s1[MAXLINE];
	char s2[MAXLINE];

	while(getline(s1, MAXLINE)) {
		expand(s1, s2);
		printf("%s\n%s\n", s1, s2);
	}

	return 0;
}

void expand(char s1[], char s2[])
{
	int i, j, k;
	for (i = k = 0; s1[i] != '\0'; ++i) {
		if (s1[i] == '-')
			if (i == 0 || s1[i+1] == '\0')
				s2[k++] = '-';
			else
				for (j = s1[i-1]; j <= s1[i+1]; ++j)
					s2[k++] = j;
	}
	s2[k] = '\0';
}

int getline(char s[], int maxline)
{
	int i, c;
	for (i = 0; i < maxline && (c = getchar()) != EOF && c != '\n'; ++i)
		s[i] = c;
	s[i] = '\0';

	return i;
}
