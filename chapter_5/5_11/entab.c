#include <stdio.h>
#include <stdlib.h>

#define getline __getline
#define MAXLINE 1000
#define TABSTOP 8

char line[MAXLINE];

int getline(void);
void entab(int);

int main(int argc, const char *argv[])
{
	int tabstop;
	if (argc == 2) {
		tabstop = atoi(argv[1]);
	} else if (argc == 1) {
		int tabstop = TABSTOP;
	} else {
		printf("error; too many arg\n");
		return -1;
	}

	int len;
	while((len = getline()) > 0) {
		entab(tabstop);
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

void entab(int tabstop)
{
	int i, j, k;
	extern char line[];
	char tmp[MAXLINE];
	for (i = 0; (tmp[i] = line[i]) != '\0'; ++i)
		;
	for (i = 0, j = 0; tmp[i] != '\0';) {
		if (tmp[i] == ' ') {
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