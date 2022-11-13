#include <stdio.h>

unsigned rightrot(unsigned, int);

int main()
{
	printf("%08x\n", rightrot(0x12345678, 8));

	return 0;
}

unsigned rightrot(unsigned x, int n)
{	
	x = x >> n | (x << (8 * sizeof(x) - n));

	return x;
}

