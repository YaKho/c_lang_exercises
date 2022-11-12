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
	int i, c;
	int cnt[11]; // (, ), {, }, [, ], ", ', /*, */, \...
	for (i = 0; i < 11; ++i)
		cnt[i] = 0;
	for (i = 0; i < maxline && (c = getchar()) != EOF; ++i) {
		switch(c) {
		case '(' :
			++cnt[0];
			break;
		case ')' :
			++cnt[1];
			break;
		case '{' :
			++cnt[2];
			break;
		case '}' :
			++cnt[3];
			break;
		case '[' :
			++cnt[4];
			break;
		case ']' :
			++cnt[5];
			break;
		case '\"' :
			++cnt[6];
			break;
		case '\'' :
			++cnt[7];
			break;			
		default : break;
		}
		if (s[i-1] == '/' && c == '*' && i > 0)
			++cnt[8];
		if (s[i-1] == '*' && c == '/' && i > 0)
			++cnt[9];

		s[i] = c;
	}
	s[i] = '\0';

	if (cnt[0] != cnt[1])
		printf("error: missing \'( )\'\n");
	if (cnt[2] != cnt[3])
		printf("error: missing \'{ }\'\n");
	if (cnt[4] != cnt[5])
		printf("error: missing \'[ ]\'\n");
	if (cnt[6] % 2)
		printf("error: missing \'\"\'\n");
	if (cnt[7] % 2)
		printf("error: missing \'\'\'\n");
	if (cnt[8] != cnt[9])
		printf("error: missing \'/* */\'\n");

	return i;
}