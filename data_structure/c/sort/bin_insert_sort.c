#include <stdio.h>

void bin_sort(int a[], int n)
{
	int i, j;
	int place;
	int tmp;

	for (i = 1; i < n; i++)
	{
		place = bin_search(a, i, a[i]);

		tmp = a[i];

		memmove(a + place + 1, a + place, (i - place) * sizeof(a[0]));

		a[place] = tmp;
	}
}
