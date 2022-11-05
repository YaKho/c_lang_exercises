#include <stdio.h>

/* print temperature table by Fahrenheit and Celsius */

float ftoc(int);

main()
{
	int fahr;
	for (fahr = 0; fahr <= 300; fahr = fahr + 20)
		printf("%3d %6.1f\n", fahr, ftoc(fahr));
}

float ftoc(int fahr)
{
	return (5.0/9.0) * (fahr-32);
}