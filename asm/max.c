#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

extern int _max(int a[], int n);

int main(int argc, char *argv[])
{
	int a[] = {4, 5, 0, 7, 1, 9, 3, 4};

	printf("MAX = %d\n", _max(a, ARRAY_LEN(a)));

	return 0;
}
