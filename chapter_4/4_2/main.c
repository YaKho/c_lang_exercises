#include <stdio.h>
#include <ctype.h>

double atof(char s[]);

int main()
{
	char s[] = "25.5e+2";

	printf("%f\n", atof(s));

	return 0;
}

double atof(char s[])
{
	double val, power;
	int i, sign, esign, j, epower;
	for (i = 0; isspace(s[i]); i++)
		;
	sign = (s[i] == '-') ? -1 : 1;
	if (s[i] == '+' || s[i] == '-')
		i++;
	for (val = 0.0; isdigit(s[i]); i++)
		val = 10.0 * val + (s[i] - '0');
	if (s[i] == '.')
		i++;
	for (power = 1.0; isdigit(s[i]); i++) {
		val = 10.0 * val + (s[i] - '0');
		power *= 10.0;
	}
	if (s[i] == 'e' || s[i] == 'E') {
		i++;
		esign = s[i++];
	}
	for (epower = 0; isdigit(s[i]); i++) {
		epower = 10 * epower + (s[i] - '0');
	}
	for (j = epower; j > 0; j--) {
		if (esign == '-')
			power *= 10;
		else if (esign == '+')
			power /= 10;
	}

	return sign * val / power;
}
