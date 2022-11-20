#include <stdio.h>
#include <stdlib.h>

#define itob __itob

void reverse(char s[]);
void itob(int n, char s[], int b);

int main()
{
	int n = 127;
	char s[100];

	itob(n, s, 16);
	printf("%s\n", s);

	return 0;
}

void itob(int n, char s[], int b)
{
	int i, sign, d;
	sign = n;
	i = 0;
	do {
		if ((d = abs(n % b)) >= 10)
			s[i++] = (d - 10) + 'a';
		else
			s[i++] = d + '0';
	} while ((n /= b));
	if (sign < 0)
		s[i++] = '-';
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
