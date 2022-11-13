#include <stdio.h>

int binsearch(int, int[], int n);

int main()
{
	int a[] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144};
	printf("%d\n", binsearch(89, a, 11));

	return 0;
}

int binsearch(int x, int v[], int n)
{	
	int low, high, mid;

	low = 0;
	high = n - 1;
	mid = (low + high) / 2;
	while(low <= high && v[mid] != x) {
		mid = (low + high) / 2;
		if (x < v[mid])
			high = mid - 1;
		else
			low = mid + 1;
	}
	if (x == v[mid])
		return mid;
	else
		return -1;
}


