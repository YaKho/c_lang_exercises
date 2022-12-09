#include <stdio.h>
#include <ctype.h>

int main(int argc, const char *argv[])
{
	int c;
	while((c = getchar()) != EOF)
		if (isprint(c))
			putchar(c);
		else
			printf("\n0x%x\n", c);

	return 0;
}
