#include <stdio.h>

#define isupperp(expr) ((expr) >= 'A' && (expr) <= 'Z') ? 1 : 0 // more place

int isuppert(int c);

int main(int argc, char const *argv[])
{
	int c = getchar();
	printf("%d, %d\n", isupperp(c), isuppert(c));

	return 0;
}

int isuppert(int c) // more time
{
	if (c >= 'A' && c <= 'Z')
		return 1;
	else
		return 0;
}
