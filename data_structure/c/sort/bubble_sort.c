#include <stdio.h>
#include <stdlib.h>

#define ARRAY_SIZE(a) (sizeof(a) / sizeof (a[0]))

#define SWAP(x, y) do { \
						__typeof(x) tmp = (x);\
						(x) = (y);\
						(y) = tmp;\
					}while(0)

void bubble_sort(int a[], int n)
{
	int i, j;

	for (i = 0; i < n - 1; i++)
	{
		for (j = 0; j < n - i - 1; j++)
		{
			if (a[j] < a[j + 1])
			{
				SWAP(a[j], a[j + 1]);
			}
		}
	}
}

int str2i(const char *str)
{
	int val;

	val = 0;

	while (*str)
	{
		val = val * 10 + *str - '0';
		str++;
	}

	return val;
}

int main(int argc, char *argv[])
{
	int i;
	int len;

	if (argc == 1)
	{
		return -1;
	}

	len = str2i(argv[1]);

	int a[len];

	for (i = 0; i < len; i++)
	{
		a[i] = random() % len;
	}

	bubble_sort(a, ARRAY_SIZE(a));

	for (i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
