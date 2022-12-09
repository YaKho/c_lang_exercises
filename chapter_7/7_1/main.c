#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	int c, reg = -1;
	char *s;
	if ((s = strstr(argv[0], "tolower.exe")) != NULL)
		reg = 0;
	else if ((s = strstr(argv[0], "toupper.exe")) != NULL)
		reg = 1;

	if (reg == -1)
		return -1;

	while ((c = getchar()) != EOF)
		if (reg)
			putchar(toupper(c));
		else
			putchar(tolower(c));

	return 0;
}
