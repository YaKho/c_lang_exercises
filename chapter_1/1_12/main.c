#include <stdio.h>

main()
{
	int c, pc;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\n') {
			if (pc != ' ' && pc != '\t' && pc != '\n')
				putchar('\n');
		} else
			putchar(c);
		pc = c;
	}
}
