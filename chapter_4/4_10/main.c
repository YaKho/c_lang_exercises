#include <stdio.h>
#include <stdlib.h> // for atof()
#include <math.h>

#define getline __getline
#define MAXOP 100 // max size operand or operator
#define MAXLINE 100
#define NUMBER '0' // sing of number

int getop (char []);
void push (double);
double pop (void);
double printop(void);
void copytop(void);
void swaptop(void);
void erase(void);
int getline(char s[], int maxline);

char line[MAXLINE];
int lpos;

// calculator with reverse polish notation
int main(void) {
	int type;
	double op2, mem;
	char s[MAXOP];
	while(getline(line, MAXLINE)) {
		lpos = 0;
		while ((type = getop(s)) != '\n') {
		    switch(type) {
		    case NUMBER:
		    	push(atof(s));
		      	break;
		    case '+':
		      	push(pop() + pop());
		      	break;
		    case '*':
		      	push(pop() * pop());
		      	break;
		    case '-':
		      	op2 = pop();
		      	push(pop() - op2);
		      	break;
		    case '/':
		      	op2 = pop();
		      	if (op2 != 0.0)
		        	push(pop() / op2);
		      	else
		        	printf("Error: divide by zero\n");
		      	break;
		    case '%':
		      	op2 = pop();
		      	if (op2 != 0)
		        	push((unsigned)pop() % (unsigned)op2);
		      	else
		        	printf("Error: divide by zero\n");
		      	break;
		    case 's':
		    	push(sin(pop()));
		    	break;
		    case 'e':
		    	push(exp(pop()));
		    	break;
		    case '^':
		    	push(pow(pop(), pop()));
		    	break;
		    case 'P':
		    	mem = printop();
		    	break;
		    case 'C':
		    	copytop();
		    	break;
		    case 'S':
		    	swaptop();
		    	break;
		    case 'E':
		    	erase();
		    	break;
		    case 'L':
		    	printf("\t%.8g\n", mem);
		    	break;
		    default :
		    	printf("Error: unrecognized operation %s\n", s);
		    	break;
		    }
		}
		printf("\t%.8g\n", mem = pop());
	}
	return 0;
}

#define MAXVAL 100 // max stack deep

int sp = 0; // next free position into stack
double val[ MAXVAL ]; // stack

// push: put value to stack
void push(double f) {
  	if (sp < MAXVAL)
    	val[sp++] = f;
  	else
    	printf("Error: stack is full, %g can't put to stack\n", f);
}

// pop: get from top stack and give as result
double pop(void) {
  	if (sp > 0)
    	return val[--sp];
  	else {
    	printf("Error: stack is empty\n");
    	return 0.0;
  	}
}

double printop(void)
{
	if (sp) {
		printf("Top value: %.8g\n", val[sp-1]);
		return val[sp-1];
	}
	else {
		printf("Error: stack is empty\n");
		return 0;
	}
}

void copytop(void)
{
	if (sp) {
		val[sp] = val[sp-1];
		sp++;
	} else
		printf("Error: stack is empty\n");
}

void swaptop(void)
{
	double tmp;
	if (sp >= 2) {
		tmp = val[sp-1];
		val[sp-1] = val[sp-2];
		val[sp-2] = tmp;
	} else
		printf("Error: stack is empty\n");
}

void erase(void)
{
	sp = 0;
}

#include <ctype.h>

// getop: get next operator or operand
int getop(char s[]) {
  	int i, c;
  
  	while ((s[0] = c = line[lpos++]) == ' ' || c == '\t');
  	s[1] = '\0';
  	if (!isdigit(c) && c != '.' && c != '-')
    	return c; // not digit
  	i = 0;
  	if (c == '-')
    	while (isdigit(s[++i] = c = line[lpos++]));
  	if (isdigit(c)) // accumulate whole part
    	while (isdigit(s[++i] = c = line[lpos++]));
  	if (c == '.') // accumulate fractional part
    	while (isdigit(s[++i] = c = line[lpos++]));
  	s[i] = '\0';
  	lpos--;
  	if ((c = s[i-1]) == '-')
    	return c; // not digit
  	return NUMBER;
}

int getline(char s[], int maxline)
{
	int i, c;
	for (i = 0; i < maxline && (c = getchar()) != EOF && c != '\n'; i++)
		s[i] = c;
	if (c == '\n')
		s[i++] = c;
	s[i] = '\0';
	return i;
}