#include <stdio.h>
#include <string.h>

#define MAXLINE 1000
#define LINEPERPAGE 9

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	int c, page, linecnt;
	FILE *p;

	while (--argc > 0) {
		if ((p = fopen(*++argv, "r")) != NULL) {
			printf("\n%s:\n", *argv);
			page = 0;
			linecnt = 0;
			while (fgets(line, MAXLINE, p) != NULL) {
				if (linecnt == 0)
					printf("\tPage %d\n", ++page);
				linecnt++;
				printf("%s", line);
				if (linecnt == LINEPERPAGE)
					linecnt = 0;
			}
			fclose(p);
		} else
			printf("\nerror: can't open file '%s'\n", *argv);
	}
	return 0;
}
