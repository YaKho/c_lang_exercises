#include <stdio.h>

#define NCHAR 256

main()
{
	int c, i, j;
	int cnt[NCHAR];
	for (i = 0; i < NCHAR; i++)
		cnt[i] = 0;
	while ((c = getchar()) != EOF) {
		if (c >= '!' && c <= '~')
			++cnt[c];
	}
	for (i = '!'; i < 1 + '~'; i++) {
		printf("%c ", i);
		for (j = 0; j < cnt[i]; j++)
			printf("|");
		printf("\n");
	}
}
