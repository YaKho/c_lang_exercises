#include <stdarg.h>
#include <stdio.h>

int minscanf(char *fmt, ...);

int main(int argc, char const *argv[])
{
	char s[100];
	int i;
	double d;

	scanf("%s %d %lf", s, &i, &d);
	printf("%s %d %lf \n", s, i, d);

	return 0;
}


int minscanf(char *fmt, ...)
{
	va_list ap;
	char *p, *sval;
	int *ival, i = 0;
	double *dval;
	unsigned *uval;

	va_start(ap, fmt);
	for (p = fmt; *p; p++) {
		if (*p != '%')
			continue;
		
		switch (*++p) {
		case 'd':
		case 'i':
			ival = va_arg(ap, int *);
			scanf("%d", ival);
			i++;
			break;
		case 'f':
			dval = va_arg(ap, double *);
			scanf("%f", dval);
			i++;
			break;
		case 's':
			sval = va_arg(ap, char *);
			scanf("%s", sval);
			i++;
			break;
		case 'c':
			uval = va_arg(ap, unsigned *);
			scanf("%c", uval);
			i++;
			break;
		case 'u':
			uval = va_arg(ap, unsigned *);
			scanf("%u", uval);
			i++;
			break;
		case 'o':
			uval = va_arg(ap, unsigned *);
			scanf("%o", uval);
			i++;
			break;
		case 'x':
			uval = va_arg(ap, unsigned *);
			scanf("%x", uval);
			i++;
			break;
		case 'X':
			uval = va_arg(ap, unsigned *);
			scanf("%X", uval);
			i++;
			break;
		case 'e':
			dval = va_arg(ap, double *);
			scanf("%e", dval);
			i++;
			break;
		case 'g':
			dval = va_arg(ap, double *);
			scanf("%g", dval);
			i++;
			break;
		default:
			break;
		}
	}
	va_end(ap);
	return i;
}

