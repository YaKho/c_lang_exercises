#include <stdio.h>

/* print temperature table by Fahrenheit and Celsius for 
celsius = 0, 20 ... 300; variant with float dot */

main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower = 0; /* bottom line of temparature table */
	upper = 300; /* top line */
	step = 20; /* step */

	celsius = lower;
	printf("Celsius to Fahrenheit\n");
	while (celsius <= upper) {
		fahr = (celsius/(5.0/9.0)) + 32.0;
		printf("%3.0f %6.1f\n", celsius, fahr);
		celsius = celsius + step;
	}
}
