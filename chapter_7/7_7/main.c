#include <stdio.h>
#include <string.h>

#define MAXLINE 1000

int main(int argc, char const *argv[])
{
	char line[MAXLINE];
	long lineno = 0;
	int c, fnum, except = 0, number = 0, found = 0;
	FILE *p;

	while (--argc > 0 && (*++argv)[0] == '-')
		while (c = *++argv[0])
			switch (c) {
			case 'x':
				except = 1;
				break;
			case 'n':
				number = 1;
				break;
			default:
				printf("find: wrong parameter %c", c);
				argc = 0;
				found = -1;
				break;
			}
	if (argc == 0)
		printf("Use: find -x -n sample file\n");
	else if (argc == 1) {
		while (fgets(line, MAXLINE, stdin) != NULL) {
			lineno++;
			if ((strstr(line, *argv) != NULL) != except) {
				if (number)
					printf("%ld:", lineno);
				printf("%s", line);
				found++;
			}
		}
	} else {
		fnum = 1;
		while (--argc > 0) {
			printf("%s:\n", argv[fnum]);
			p = fopen(argv[fnum], "r");
			while (fgets(line, MAXLINE, p) != NULL) {
				lineno++;
				if ((strstr(line, *argv) != NULL) != except) {
					if (number)
						printf("%ld:", lineno);
					printf("%s", line);
					found++;
				}
			}
			fclose(p);
			fnum++;
			lineno = 0;
		}
	}
	return found;
}
