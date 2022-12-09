#include <stdio.h>
#include <stdlib.h> // for atof()
#include <string.h>

#define MAXOP 100 // max size operand or operator
#define NUMBER '0' // sing of number

void push (double);
double pop (void);

// calculator with reverse polish notation
int main(void) {
	int type;
	double op2, num;
	char s[MAXOP], c;
	while (scanf("%s%c", s, &c) == 2) {
		if (sscanf(s, "%lf", &num) == 1)
			push(num);
		else if (strlen(s) == 1) {
		    switch (*s) {
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
		    default :
		      	printf("Error: unrecognized operation %s\n", s);
		      	break;
		    }
		} else
			printf("Error: unrecognized operation %s\n", s);
		if (c == '\n')
			printf("\t%.8g\n", pop());
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
