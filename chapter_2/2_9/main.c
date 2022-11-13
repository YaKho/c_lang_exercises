#include <stdio.h>

int bitcount(unsigned);

int main()
{
	printf("%d\n", bitcount(0xf000f00f));

	return 0;
}

int bitcount(unsigned x)
{	
	int b;
	for (b = 0; x != 0; b++)
		x &= (x - 1);

	return b;
}

