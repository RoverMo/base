#include <stdio.h>

#define LEN(a) (sizeof((a)) / sizeof((a)[0]))

static void merge(int a[], int start, int mid, int end)
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

static void merge_sort(int a[], int start, int end)
{
	int mid;

	if (start < end)
	{
		mid = (start + end) >> 1;
		merge_sort(a, start, mid);
		merge_sort(a, mid + 1, end);
		merge(a, start, mid, end);
	}
}

int main()
{
	int a[] = {6, 8, 1, 4, 3, 12, 0, 15, 9 ,-1};
	int i;

	merge_sort(a, 0, LEN(a) - 1);

	for (i = 0; i < LEN(a); i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
