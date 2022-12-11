#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef long Align;

union header {
    struct {
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};
typedef union header Header;

void *bfree(void *p, size_t n);

int main()
{
    char *a = NULL, b[sizeof(Header)], c[sizeof(Header) * 2];
    bfree(a, sizeof(a));
    bfree(b, sizeof(b));
    bfree(c, sizeof(c));
    char *d = malloc(sizeof(Header));
    d[0] = '!';
    free(d);
    return 0;
}

void *bfree(void *p, size_t n) {
	if (n < sizeof(Header))
		return NULL;

	Header *bp = (Header *)p;
	bp->s.size = n / sizeof(Header);
  	free(bp + 1);
}