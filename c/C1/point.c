#include <stdio.h>

int main()
{
	int a, b;
	int *p;

	a = 10;
	p = &a;

	printf("*p = %d, a = %d\n", *p, a);

	*p = 12;
	printf("*p = %d, a = %d\n", *p, a);

	a = 14;
	printf("*p = %d, a = %d\n", *p, a);

	return 0;
}
