#include <stdio.h>

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

#define SWAP(x, y) do { \
						__typeof(x) t = (x); \
						(x) = (y); \
						(y) = (t); \
					} while(0)

void heap_sort(int a[], int n)
{
	int parent, child;
	int i, j;

	for (j = 1; j < n; j++)
	{
		for (i = n - j; i > 0;)
		{
			parent = (i - 1) >> 1;
			if (i & 1)
			{
				if (a[parent] < a[i])
				{
					SWAP(a[parent], a[i]);
				}
				i--;
			}
			else
			{
				if (a[i] > a[i - 1])
				{
					child = i;
				}
				else
				{
					child = i - 1;
				}

				if (a[parent] < a[child])
				{
					SWAP(a[parent], a[child]);
				}
				i -= 2;
			}
		}
		SWAP(a[0], a[n - j]);
	}
}

/*
int main(int argc, char *argv[])
{
	int i;
	int a[] = {3, 1, 5, 6, 2, 9, 5, 6, 7, 0};

	heap_sort(a, ARRAY_LEN(a));

	for (i = 0; i < ARRAY_LEN(a); i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
*/

