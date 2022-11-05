#include <stdio.h>

#define MAXLEN 20

main()
{
	int c, cl, i, j;
	int wlen[MAXLEN];
	for (i = 0; i < MAXLEN; i++)
		wlen[i] = 0;
	cl = 0;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			wlen[cl]++;
			cl = 0;
		}
		else
			if (cl < MAXLEN)
				cl++;
	}
	for (i = 1; i < MAXLEN; i++) {
		printf("%2d ", i);
		for (j = 0; j < wlen[i]; j++)
			printf("|");
		printf("\n");
	}
}
