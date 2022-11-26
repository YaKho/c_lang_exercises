#include <stdio.h>

void itoa(char s[], int d);

int main(void) {
	char s[1000];
	int n = 123;
	itoa(s, n);
	printf("%s\n", s);

	return 0;
}

void itoa(char s[], int d)
{
	static int i = 0;
	if (d < 0) {
		s[i++] = '-';
		d = -d;
	}
	if (d/10)
		itoa(s, d/10);
	s[i++] = d % 10 + '0';
	s[i] = '\0';
}
