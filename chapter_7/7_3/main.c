#include <stdarg.h>
#include <stdio.h>

void minprintf(char *fmt, ...);

int main(int argc, char const *argv[])
{
	minprintf("it %s %d %f\n", "is", 10, 2.5);

	return 0;
}


void minprintf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int ival;
	double dval;
	unsigned uval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%') {
			putchar(*p);
			continue;
		}
		switch (*++p) {
		case 'd':
		case 'i':
			ival = va_arg(ap, int);
			printf("%d", ival);
			break;
		case 'f':
			dval = va_arg(ap, double);
			printf("%f", dval);
			break;
		case 's':
			for (sval = va_arg(ap, char *); *sval; sval++)
				putchar(*sval);
			break;
		case 'c':
			ival = va_arg(ap, int);
			putchar(ival);
			break;
		case 'u':
			uval = va_arg(ap, unsigned);
			printf("%u", uval);
			break;
		case 'o':
			uval = va_arg(ap, unsigned);
			printf("%o", uval);
			break;
		case 'x':
			uval = va_arg(ap, unsigned);
			printf("%x", uval);
			break;
		case 'X':
			uval = va_arg(ap, unsigned);
			printf("%X", uval);
			break;
		case 'e':
			dval = va_arg(ap, double);
			printf("%e", dval);
			break;
		case 'g':
			dval = va_arg(ap, double);
			printf("%g", dval);
			break;
		case '%':
			putchar(*p);
			break;
		default:
			putchar('%');
			putchar(*p);
			break;
		}
	}
	va_end(ap);
}
