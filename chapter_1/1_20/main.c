#include <stdio.h>

#define getline __getline
#define MAXLINE 1000
#define TABSTOP 8

char line[MAXLINE];

int getline(void);
void detab(void);

main()
{
	int len;
	while((len = getline()) > 0) {
		detab();
		printf("%s", line);
	}

	return 0;
}

int getline(void)
{
	int c, i;
	extern char line[];

	for (i=0; i < MAXLINE-1 && (c = getchar()) != EOF && c != '\n'; ++i)
		line[i] = c;
	if (c == '\n') {
		line[i] = c;
		++i;
	}
	line[i] = '\0';
	return i;
}

void detab(void)
{
	int i, j, k;
	extern char line[];
	char tmp[MAXLINE];
	for (i = 0; (tmp[i] = line[i]) != '\0'; ++i)
		;
	for (i = 0, j = 0; tmp[i] != '\0'; ++i) {
		if (tmp[i] == '\t') {
			if (j % TABSTOP == 0)
				for (k = 0; k < TABSTOP; ++k, ++j)
					line[j] = ' ';
			else
				for (; j % TABSTOP > 0; ++j)
					line[j] = ' ';
		} else
			line[j++] = tmp[i];
	}
	line[j] = '\0';
}
