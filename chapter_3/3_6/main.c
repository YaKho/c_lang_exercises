#include <stdio.h>
#include <stdlib.h>

#define itoa __itoa

void reverse(char s[]);
void itoa(int n, char s[], int f);

int main()
{
	int n = 11;
	char s[1000];

	itoa(n, s, 8);
	printf("%s\n", s);

	return 0;
}

void itoa(int n, char s[], int f)
{
	int i, sign;
	i = 0;
	do {
		s[i++] = abs(n % 10) + '0';
	} while ((n /= 10));
	if (sign < 0)
		s[i++] = '-';
	while(i < f)
		s[i++] = ' ';
	s[i] = '\0';
	reverse(s);
}

// from ex.1.19
void reverse(char s[])
{
	int i, cnt;
	for (cnt = 0; s[cnt] != '\0'; ++cnt)
		;
	char tmp[cnt];
	for (i = 0; (tmp[i] = s[i]) != '\0'; ++i)
		;
	for (i = 0; cnt > 0; ++i, --cnt)
		s[i] = tmp[cnt-1];
	s[i] = '\0';
}
