#include <stdio.h>
#include <stdlib.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

void insert_sort(int a[], int n)
{
	int i, j;
	int tmp;

	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i - 1; j >= 0; j--)
		{
			if (tmp >= a[j])
			{
				break;
			}
			else
			{
				a[j + 1] = a[j];
			}
		}

		if (j != i - 1)
		{
			a[j + 1] = tmp;
		}
	}
}
/*
int main(int argc, char *argv[])
{
	int a[] = {4, 8, 2, 9, 1, 0, 3, 3, 5};
	int i;
	int len = ARRAY_LEN(a);

	insert_sort(a, len);

	for (i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}*/
