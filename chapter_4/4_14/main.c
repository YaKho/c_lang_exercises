#include <stdio.h>

#define swap(t, x, y) {t tmp;\
					tmp = y;\
					y = x;\
					x = tmp;}
					
int main(void)
{
	char s[] = "hello";

	swap(char, s[0], s[4]);
	printf("%s\n", s);

	return 0;
}
