#include <stdio.h>

unsigned invert(unsigned, int, int);

int main()
{
	printf("%08x\n", invert(0xaaaaaaaa, 8, 16));

	return 0;
}

unsigned invert(unsigned x, int p, int n)
{
	x = (x & ~(~(0xffffffff << n) << p)) | (~x & (~(0xffffffff << n) << p));

	return x;
}
