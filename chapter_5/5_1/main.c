#include <stdio.h>
#include <ctype.h>

int getint(int*);

int main(void)
{
	int dig;
	while(getint(&dig) != EOF);
	printf("%d\n", dig);

	return 0;
}

int getch(void);
void ungetch(int);

int getint(int *pn)
{
	int c, sign;
	while(isspace(c = getch()))
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c);
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-')
		if (!isdigit(c = getch()) && c != EOF) {
			(sign > 0) ? ungetch('+') : ungetch('-');
			return 0;
		}

	for (*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buffer

// get (possibly returned) character
int getch(void) {
  	return (bufp > 0) ? buf[--bufp] : getchar();
}

// return character to input
void ungetch(int c) {
  	if (bufp >= BUFSIZE)
    	printf("ungetch: too many characters\n");
  	else
    	buf[bufp++] = c;
}