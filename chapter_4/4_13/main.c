#include <stdio.h>

void reverse(char s[]);

int main(void)
{
	char s[] = "hello";
	reverse(s);
	printf("%s\n", s);
	return 0;
}

void reverse(char s[])
{
	static int i = 0;
	int j = 0;
	char tmp;
	while(s[j] != '\0')
		j++;
	j -= i + 1;
	if (i < j) {
		tmp = s[j];
		s[j] = s[i];
		s[i++] = tmp;
		reverse(s);
	}
}
