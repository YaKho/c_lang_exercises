#include <stdio.h>
#include <stdlib.h>

#define getline __getline
#define MAXLINE 1000
#define TABSTOP 8

char line[MAXLINE];

int getline(void);
void detab(int, int);

int main(int argc, const char *argv[])
{
	int tabstop, start, c;

	tabstop = TABSTOP;
	start = 0;

	switch(argc) {
	case 1:
		break;
	case 2:
		if ((c = (*(argv + 1))[0]) == '-') {
			start = atoi(++argv[1]);
		} else if (c == '+') {
			tabstop = atoi(++argv[1]);
		}
		break;
	case 3:
		if ((c = (*(argv + 1))[0]) == '-') {
			start = atoi(++argv[1]);
		} else if (c == '+') {
			tabstop = atoi(++argv[1]);
		}
		if ((c = (*(argv + 2))[0]) == '-') {
			start = atoi(++argv[2]);
		} else if (c == '+') {
			tabstop = atoi(++argv[2]);	
		}
		break;
	default:
		printf("error; too many arg\n");
		return -1;
	}

	int len;
	while((len = getline()) > 0) {
		detab(start, tabstop);
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

void detab(int start, int tabstop)
{
	int i, j, k;
	extern char line[];
	char tmp[MAXLINE];
	for (i = 0; (tmp[i] = line[i]) != '\0'; ++i)
		;
	for (i = 0, j = 0; tmp[i] != '\0'; ++i) {
		if (tmp[i] == '\t' && i >= start) {
			if (j % tabstop == 0)
				for (k = 0; k < tabstop; ++k, ++j)
					line[j] = ' ';
			else
				for (; j % tabstop > 0; ++j)
					line[j] = ' ';
		} else
			line[j++] = tmp[i];
	}
	line[j] = '\0';
}

