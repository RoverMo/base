#include <stdio.h>

#define LEN 6

#define ARRAY_LEN(a) (sizeof(a) / sizeof(a[0]))

int bin_search(int a[], int n, int num)
{
	int index;
	int start, end;

	start = 0;
	end   = n - 1;

	while (start <= end)
	{
		index = (start + end) >> 1;

		if (a[index] > num)
		{
			end = index - 1;
		}
		else if (a[index] < num)
		{
			start = index + 1;
		}
		else
		{
			break;
		}
	}

	if (a[index] > num)
	{
		index--;
	}

	return index;
}

int bin_search1(int a[], int n, int num)
{
	int index;
	int start, end;

	for (start = 0, end = n - 1; start <= end;)
	{
		index = (start + end) >> 1;

		if (a[index] > num)
		{
			end = index - 1;
		}
		else if (a[index] < num)
		{
			start = index + 1;
		}
		else
		{
			break;
		}
	}

	if (a[index] > num)
	{
		index--;
	}

	return index;
}
/*
int main(int argc, char *argv[])
{
	int ret;
	int a[6] = {1, 2, 2, 5, 6};

	ret = bin_search(a, ARRAY_LEN(a) - 1, 3);
	printf("ret = %d\n", ret);

	ret = bin_search(a, ARRAY_LEN(a) - 1, 3);
	printf("ret = %d\n", ret);

	return 0;
}
*/
