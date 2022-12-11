#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define calloc __calloc

void *calloc(int n, size_t size);

int main(int argc, char const *argv[])
{
	unsigned *p;
	int i, size = 10, n = 10;
	
	p = calloc(n, sizeof(*p));
	
	for (i = 0; i < n; i++)
		printf("%08x\n", *p++);
	free(p);

	return 0;
}

void *calloc(int n, size_t size)
{
	void *p;

	if ((p = malloc(n * size)) == NULL)
		return NULL;
	memset(p, 0x0, n * size);

	return p;
}