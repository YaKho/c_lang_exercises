#include <stdio.h>

main()
{
	int c, sp;
	while ((c = getchar()) != EOF) {
		if (c == ' ') {
			if (sp != ' ')
				putchar(c);
		} else
			putchar(c);
		sp = c;
	}
}
