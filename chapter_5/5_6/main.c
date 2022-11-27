#include <stdio.h>
#include <string.h>

#define getline __getline
#define atoi __atoi
#define itoa __itoa
#define reverse __reverse
#define strindex __strindex
#define MAXLINE 1000

int getline(char*, int);
int atoi(char*);
void itoa(int, char*);
void reverse(char*);
int strindex(char*, char*);
int getop(char *s);

int main(void)
{
	int d;
	char line[MAXLINE];
	getline(line, MAXLINE);
	printf("getline: %s\n", line);
	printf("atoi: %d\n", d = atoi(line));
	itoa(d, line);
	printf("itoa: %s\n", line);
	reverse(line);
	printf("reverse: %s\n", line);
	printf("strindex: %d\n", strindex(line, "321"));
	getop(line);
	printf("getop: %s\n", line);

	return 0;
}

int getline(char *s, int maxline)
{
	int c;
	char *tmp = s;
	for (; --maxline > 0 && (c = getchar()) != EOF && c != '\n'; s++)
		*s = c;
	*s = '\0';

	return s - tmp;
}

int atoi(char *s)
{
	int n = 0;
	for (; *s >= '0' && *s <= '9'; s++)
		n = 10 * n + (*s - '0');
	return n;
}

void itoa(int n, char *s)
{
	int sign = n;
	char *t = s;
	do {
		*s++ = n % 10 + '0';
	} while ((n /= 10));
	if (sign < 0)
		*s++ = '-';
	*s = '\0';
	reverse(t);
}

void reverse(char *s)
{
	int c;
	char *t;
	for (t = s + (strlen(s) - 1); s < t; s++, t--) {
		c = *s;
		*s = *t;
		*t = c;
	}
}

int strindex(char *s, char *t)
{
	char *j, *k, *sc = s;
	for (; *s != '\0'; s++) {
		for (j = s, k = t; *k != '\0' && *j == *k; j++, k++)
			;
		if (k > t && *k == '\0')
			return s - sc;
	}
	return -1;
}

#include <ctype.h>
#define NUMBER '0'

int getch(void);
void ungetch(int);

// getop: get next operator or operand
int getop(char *s) {
  	int c;
  
  	while ((*s = c = getch()) == ' ' || c == '\t');
  	*(s + 1) = '\0';
  	if (!isdigit(c) && c != '.' && c != '-')
    	return c; // not digit
  	if (c == '-')
    	while (isdigit(*++s = c = getch()));
  	if (isdigit(c)) // accumulate whole part
    	while (isdigit(*++s = c = getch()));
  	if (c == '.') // accumulate fractional part
    	while (isdigit(*++s = c = getch()));
  	*s = '\0';
  	if (c != EOF)
    	ungetch(c);
  	if ((c = *(s-1)) == '-')
    	return c; // not digit
  	return NUMBER;
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