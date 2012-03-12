#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

void shell_sort(int a[], int n)
{
	int i, j;
	int tmp;
	int step;

	for (step = n / 2; step > 0; step /= 2)
	{
		for (i = step; i < n; i++)
		{
			tmp = a[i];
			j = i - step;

			while (j >= 0 && tmp < a[j])
			{
				a[j + step] = a[j];
				j -= step;
			}
			a[j + step] = tmp;
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	int a[] = {4, 8, 2, 9, 1, 0, 3, 3, 5};
	int len = ARRAY_LEN(a);

	shell_sort(a, len);

	for (i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
