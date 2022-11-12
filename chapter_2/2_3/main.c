#include <stdio.h>

#define getline __getline
#define MAXLINE 100

int getline(char[], int);
int htol(char[]);

int main()
{
	int c;
	char s[MAXLINE];
	while(getline(s, MAXLINE)) {
		if ((c = htol(s)) >= 0)
			printf("%d\n", c);
		else
			printf("error: \'0x\' not found\n");
	}
	return 0;
}

int getline(char s[], int maxline)
{
	int i, c;
	for (i = 0; i < maxline && (c = getchar()) != EOF 
			&& c != ' ' && c != '\t' && c != '\n'; ++i)
		s[i] = c;
	s[i] = '\0';

	return i;
}

int htol(char s[])
{
	int i, n;
	if (s[0] != '0' || (s[1] != 'x' && s[1] != 'X'))
		return -1;
	else
		for (i = 2, n = 0; s[i] != '\0'; ++i) {
			if (s[i] >= '0' && s[i] <= '9')
				n = 16 * n + (s[i] - '0');
			else if (s[i] >= 'a' && s[i] <= 'f')
				n = 16 * n + (s[i] - 'a' + 10);
			else if (s[i] >= 'A' && s[i] <= 'F')
				n = 16 * n + (s[i] - 'A' + 10);
			else
				break;
		}

	return n;
}