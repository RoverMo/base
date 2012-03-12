#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

void merge(int a[], int start, int mid, int end)
{
	const int len = end - start + 1;
	int temp[len];
	int index1 = start;
	int index2 = mid + 1;
	int i = 0;

	while (index1 <= mid && index2 <= end)
	{
		if (a[index1] < a[index2])
			temp[i++] = a[index1++];
		else
			temp[i++] = a[index2++];
	}

	while (index1 <= mid)
		temp[i++] = a[index1++];

	while (index2 <= end)
		temp[i++] = a[index2++];

	for (i = 0; i < len; i++)
		a[start + i] = temp[i];
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

	for (j = 2; j < n; j <<= 1)
	{
		printf("j = %d\n", j);
		for (i = 0; i < n; i += j)
		{
			if (i + j < n)
			{
				merge(a, i, i + j / 4, i + j / 2);
				printf("1:start = %d, mid = %d, end = %d\n", i, i + j / 4, i + j / 2);
			}
			else
			{
				merge(a, i, (i + 1) * j + j / 2, n - 1);
				printf("2:start = %d, mid = %d, end = %d\n", i, (i + 1) * j + j / 2, n - 1);
			}
			print_array(a, n);
		}
		printf("\n");
	}
}

static void recursion_merge_sort(int a[], int start, int end)
{
    int mid;

    if (start < end)
    {
        mid = (start + end) >> 1;
        recursion_merge_sort(a, start, mid);
        recursion_merge_sort(a, mid + 1, end);
        merge(a, start, mid, end);
    }
}


int main(int argc, char *argv[])
{
	int a[] = {7, 3, 2, 89, 12, 9};

#if 1
	printf("iteration:\n");
	iteration_merge_sort(a, ARRAY_LEN(a));
#else
	printf("recursion:\n");
	recursion_merge_sort(a, 0, ARRAY_LEN(a));
#endif

	print_array(a, ARRAY_LEN(a));

	return 0;
}
