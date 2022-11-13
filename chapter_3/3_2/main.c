#include <stdio.h>

#define getline __getline
#define MAXLINE 1000

int getline(char[], int);
void escape(char[], char[]);
void descape(char[], char[]);

int main()
{
	char line[MAXLINE];
	char s1[MAXLINE];
	char s2[MAXLINE];
	while(getline(line, MAXLINE)) {
		escape(s1, line);
		printf("%s\n", s1);
		descape(s2, s1);
		printf("%s\n", s2);
	}

	return 0;
}

void escape(char s[], char t[])
{
	int i, j;
	for (i = j = 0; t[i] != '\0'; ++i) {
		switch(t[i]) {
		case '\n':
			s[j++] = '\\';
			s[j++] = 'n';
			break;
		case '\t':
			s[j++] = '\\';
			s[j++] = 't';
			break;
		default:
			s[j++] = t[i];
			break;
		}
	}
	s[j] = '\0';
}

void descape(char s[], char t[])
{
	int i, j;
	for (i = j = 0; t[i] != '\0'; ++j, ++i) {
		switch(t[i]) {
		case '\\':
			switch(t[i+1]) {
			case 'n':
				s[j] = '\n';
				++i;
				break;
			case 't':
				s[j] = '\t';
				++i;
				break;
			default:
				s[j] = t[i];
				break;
			}
			break;
		default:
			s[j] = t[i];
			break;
		}
	}
	s[j] = '\0';
}

int getline(char s[], int maxline)
{
	int i, c;
	for (i = 0; i < maxline && (c = getchar()) != EOF; ++i)
		s[i] = c;
	s[i] = '\0';

	return i;
}
