#include <stdio.h>
#include <limits.h>
#include <float.h>

int main()
{
	printf("Calculated:\n");
	char c = 1;
	c <<= (8 * sizeof(char)) - 1;
	printf("char: %d to %d\n", c, ~c);
	unsigned char uc = 0;
	uc -= 1;
	printf("unsigned char size: %u to %u\n", 0, uc);
	short s = 1;
	s <<= (8 * sizeof(short)) - 1;
	printf("short: %d to %d\n", s, ~s);
	unsigned short us = 0;
	us -= 1;
	printf("unsigned short size: %u to %u\n", 0, us);
	int i = 1;
	i <<= (8 * sizeof(int)) - 1;
	printf("int: %d to %d\n", i, ~i);
	unsigned int ui = 0;
	ui -= 1;
	printf("unsigned int size: %u to %u\n", 0, ui);
	long l = 1;
	l <<= (8 * sizeof(long)) - 1;
	printf("long: %d to %d\n", l, ~l);
	unsigned long ul = 0;
	ul -= 1;
	printf("unsigned int size: %u to %u\n", 0, ul);
	float f = 1;
	f <<= (8 * sizeof(float)) - 1;
	printf("float: %g to %g\n", f, ~f);
	double d = 1;
	d <<= (8 * sizeof(double)) - 1;
	printf("double: %g to %g\n", d, ~d);

	printf("\nFrom <limits.h>:\n");
	
	printf("char: %d to %d\n", SCHAR_MIN, SCHAR_MAX);
	printf("unsigned char: %u to %u\n", 0, UCHAR_MAX);
	printf("short: %d to %d\n", SHRT_MIN, SHRT_MAX);
	printf("unsigned short: %u to %u\n", 0, USHRT_MAX);
	printf("int: %d to %d\n", INT_MIN, INT_MAX);
	printf("unsigned int: %u to %u\n", 0, UINT_MAX);
	printf("long: %d to %d\n", LONG_MIN, LONG_MAX);
	printf("unsigned long: %u to %u\n", 0, ULONG_MAX);
	printf("float: %g to %g\n", FLT_MIN, FLT_MAX);
	printf("double: %g to %g\n", DBL_MIN, DBL_MAX);

	return 0;
}
