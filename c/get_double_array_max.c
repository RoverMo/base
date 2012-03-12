/*
 * 实现一个函数。传入一个二维数组，求其最大值及所对应的行、列下标。
 */

#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#define get_array_max(a, n)				__get_array_max(a, &n)
#define get_double_array_max(a, x, y)	__get_double_array_max((int *)(a), x, y)

int __get_array_max(int *a, size_t *n)
{
	int i;
	int max;
	size_t index;

	max		= a[0];
	index	= 0;

	for (i = 1; i < *n; i++)
	{
		if (a[i] > max)
		{
			max		= a[i];
			index	= i;
		}
	}

	*n = index;

	return max;
}

int __get_double_array_max(int *a, int *m, int *n)
{
	size_t size;
	int max;

	size	= (*m) * (*n);
	max = get_array_max(a, size);

	*n = size % *m;
	*m = size / *m;

	return max;
}

int main(int argc, char *argv[])
{
	int a[][3] = {{3, 2, 1}, {6, 5, 4}, {9, 10, 8}};
	int line, row;
	int max;

	line	= ARRAY_SIZE(a);
	row		= ARRAY_SIZE(a[0]);

	max = get_double_array_max(a, &line, &row);

	printf("%d\t%d\t%d\n", max, line, row);

	return 0;
}
