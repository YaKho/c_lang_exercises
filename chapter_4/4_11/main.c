#include <stdio.h>
#include <stdlib.h> // for atof()

#define MAXOP 100 // max size operand or operator
#define NUMBER '0' // sing of number

int getop (char []);
void push (double);
double pop (void);

// calculator with reverse polish notation
int main(void) {
	int type;
	double op2;
	char s[MAXOP];
	while ((type = getop(s)) != EOF) {
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
	    case '/':
	      	op2 = pop();
	      	if (op2 != 0.0)
	        	push(pop() / op2);
	      	else
	        	printf("Error: divide by zero\n");
	      	break;
	    case '-':
	      	op2 = pop();
	      	push(pop() - op2);
	      	break;
	    case '%':
	      	op2 = pop();
	      	if (op2 != 0)
	        	push((unsigned)pop() % (unsigned)op2);
	      	else
	        	printf("Error: divide by zero\n");
	      	break;
	    case '\n':
	      	printf("\t%.8g\n", pop());
	      	break;
	    default :
	      	printf("Error: unrecognized operation %s\n", s);
	      	break;
	    }
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

#include <ctype.h>

int getch(void);

// getop: get next operator or operand
int getop(char s[]) {
  	int i;
  	static char c = ' ';
  	if (c == ' ' || c == '\t')
  		while ((s[0] = c = getch()) == ' ' || c == '\t');
  	s[1] = '\0';
  	if (!isdigit(c) && c != '.'){
  		i = c;
  		c = ' ';
    	return i; // not digit
  	}
  	i = 0;
  	if (isdigit(c)) // accumulate whole part
    	while (isdigit(s[++i] = c = getch()));
  	if (c == '.') // accumulate fractional part
    	while (isdigit(s[++i] = c = getch()));
  	s[i] = '\0';
  	return NUMBER;
}

#define BUFSIZE 100

char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0; // next free position in buffer

// get (possibly returned) character
int getch(void) {
  	return (bufp > 0) ? buf[--bufp] : getchar();
}