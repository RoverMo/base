#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

void merge(int a[], int n)
{
	int i, j, k;
	int mid;
	int tmp[n];

	mid = n >> 1;
	i = 0;
	j = mid;
	k = 0;

	while (i <= mid && j < n)
	{
		if (a[i] < a[j])
			temp[k++] = a[i++];
		else
			temp[k++] = a[j++];
	}

	while (i <= mid)
		temp[k++] = a[i++];

	while (j < n)
		temp[k++] = a[j++];

	for (i = 0; i < n; i++)
		a[i] = temp[i];
}

void print_array(int a[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");
}

void iteration_merge_sort(int a[], int n)
{
	int i, j;

	if (n == 1)
	{
		return;
	}

	for (i = 2; i < n; i <<= 1)
	{
		for (j = 0; j + i <= n; j += i;)
		{
			merge(a[j * i], i);
		}
	}
}


int main(int argc, char *argv[])
{
	int a[] = {7, 3, 2, 89, 12, 9};

	iteration_merge_sort(a, ARRAY_LEN(a));

	print_array(a, ARRAY_LEN(a));

	return 0;
}
