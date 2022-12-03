#include <stdio.h>

int day_of_year(int year, int month, int day);
void month_day(int year, int yearday, int *pmonth, int *pday);

int main(void) {
	int month, day;

	month_day(1991, 346, &month, &day);

	printf("day_of_year: %d\nmonth: %d, day: %d\n", day_of_year(1991, 12, 12), month, day);

	return 0;
}

static char daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// day_of_year: defines day of year by month and day
int day_of_year(int year, int month, int day) {
	int leap;
	char *ptr;
	if (year < 1 || month < 1 || month > 12)
		return -1;
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	ptr = daytab[leap];
	if (day < 1 || day > *(ptr + month))
		return -1;
	while (month) {
		day += *ptr++;
		month--;
	}
	return day;
}

// month_day: defines month and day by day of year
void month_day(int year, int yearday, int *pmonth, int *pday) {
	int leap;
	char *ptr;
	if (year < 1) {
		*pmonth = *pday = -1;
		return;
	}
	leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
	if (yearday < 1 || yearday > 365 + leap) {
		*pmonth = *pday = -1;
		return;
	}
	ptr = daytab[leap];
	*pmonth = 0;
	while (yearday > *ptr) {
		yearday -= *ptr++;
		(*pmonth)++;
	}
	*pday = yearday;
}