#include <stdio.h>
#include <stdlib.h>

#define getline __getline
#define MAXLINE 1000
#define TABSTOP 8

char line[MAXLINE];

int getline(void);
void entab(int, int);

int main(int argc, const char *argv[])
{
	int tabstop, start, c;

	switch(argc) {
	case 1:
		tabstop = TABSTOP;
		start = 0;
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
		entab(start, tabstop);
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

void entab(int start, int tabstop)
{
	int i, j, k;
	extern char line[];
	char tmp[MAXLINE];
	for (i = 0; (tmp[i] = line[i]) != '\0'; ++i)
		;
	for (i = 0, j = 0; tmp[i] != '\0';) {
		if (tmp[i] == ' ' && i >= start) {
			for (k = 0; tmp[i+k] == ' ';) // count spaces
				++k;
			if (k >= tabstop - i % tabstop) { // if there are enough 
				line[j++] = '\t';			  // spaces to the next stop
				i += tabstop - i % tabstop;
			} else
				line[j++] = tmp[i++];
		} else
			line[j++] = tmp[i++];
	}
	line[j] = '\0';
}