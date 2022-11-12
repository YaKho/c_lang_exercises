#include <stdio.h>

int main()
{
	int i, c, lim = 100;
	char s[lim];	
	for (i = 0; i < lim-1; ++i) {
		if ((c = getchar()) == EOF)
			break;
		else if (c == '\n')
			break;
		else
			s[i] = c;
	}
	s[i] = '\0';
	printf("%s\n", s);

	return 0;
}
