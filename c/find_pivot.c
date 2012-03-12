/*
 * 以a[0]为轴，左边小于a[0],右边大于a[0]。
 */
#include <stdio.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

static int find_pivot(int a[], size_t n)
{
	int i, j;
	int index;
	int tmp[n];

	i = 0;
	j = n - 1;
	index = 1;

	while (i < j)
	{
		if (a[0] >= a[index])
		{
			tmp[i] = a[index];
			i++;
		}
		else
		{
			tmp[j] = a[index];
			j--;
		}
		index++;
	}
	tmp[i] = a[0];

	for (i = 0; i < n; i++)
	{
		a[i] = tmp[i];
	}

	return j;
}

int main(int argc, char *argv[])
{
	int i;
	int a[] = {5};
	int pivot;

	pivot = find_pivot(a, ARRAY_SIZE(a));

	for (i = 0; i < ARRAY_SIZE(a); i++)
	{
		printf("%d\n", a[i]);
	}

	return 0;
}
