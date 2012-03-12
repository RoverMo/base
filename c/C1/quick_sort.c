#include <stdio.h>

#define LEN(a) (sizeof((a)) / sizeof((a)[0]))

static int find_pivot(int a[], int start, int end)
{
	const int len = end - start + 1;
	int temp[len];
	int i = 0;
	int j = len - 1;
	int index = start + 1;
	int tmp = a[start];

	while (i != j)
	{
	    if (tmp < a[index])
	        temp[j--] = a[index++];
	    else
	        temp[i++] = a[index++];
	}
	temp[i] = tmp;

	for (i = 0; i < len; i++)
	    a[start + i] = temp[i];

	return start + j;
}

static int find_pivot1(int a[], int start, int end)
{
	int temp = a[start];

	while (start != end)
	{
		while (a[end] >= temp && start < end)
			end--;
		a[start] = a[end];

		while (a[start] < temp && start < end)
			start++;
		a[end] = a[start];
	}
	a[start] = temp;

	return start;
}

static void quick_sort(int a[], int start, int end)
{
	int pivot;

	if (start < end)
	{
		pivot = find_pivot(a, start, end);
		quick_sort(a, start, pivot - 1);
		quick_sort(a, pivot + 1, end);
	}
}

int main()
{
	int a[] = {1, 4, 3, 12, 0, 15, 9};
	int i;

	quick_sort(a, 0, LEN(a) - 1);

	for (i = 0; i < LEN(a); i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
