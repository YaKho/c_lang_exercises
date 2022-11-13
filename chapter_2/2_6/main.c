#include <stdio.h>

unsigned setbits(unsigned, int, int, unsigned);

int main()
{
	printf("%08x\n", setbits(0x12345678, 8, 16, 0xffffabcd));

	return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
	x = (x & ~(~(0xffffffff << n) << p)) | ((y & ~(0xffffffff << n)) << p);

	return x;
}