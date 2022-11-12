#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);

int main()
{
	char line[MAXLINE];

	while(getline(line, MAXLINE)) {
		printf("\n%s", line);
	}
	return 0;
}

int getline(char s[], int maxline)
{
	int i, c, pre, instr;
	instr = 0;
	for (i = 0; i < maxline && (c = getchar()) != EOF;) {
		if (c == '"')
			if (instr)
				instr = 0;
			else
				instr = 1;
		if (s[i-1] == '/' && i > 0 && instr == 0) {
			if (c == '/') {
				s[i-1] = '\n';
				while((c = getchar()) != '\n' && c != EOF)
					;
			} else if (c == '*') {
				s[i-1] = '\n';
				while((c = getchar()) != EOF && !(c == '/' && pre == '*'))
					pre = c;
			}
		} else
			s[i++] = c;
	}
	s[i] = '\0';

	return i;
}
