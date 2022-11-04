#include <stdio.h>

/* print temperature table by Fahrenheit and Celsius for 
fahr = 0, 20 ... 300; variant with float dot */

main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; /* bottom line of temparature table */
	upper = 300; /* top line */
	step = 20; /* step */

	fahr = lower;
	printf("Fahrenheit to Celsius\n");
	while (fahr <= upper) {
		celsius = (5.0/9.0) * (fahr-32.0);
		printf("%3.0f %6.1f\n", fahr, celsius);
		fahr = fahr + step;
	}
}
