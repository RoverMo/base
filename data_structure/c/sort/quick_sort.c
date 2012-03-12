#include <stdio.h>
#include <stdlib.h>

int find(int a[], int n)
{
	int i, j;
	int tmp;

	i = 0;
	j = n - 1;
	tmp = a[0];

	while (i < j)
	{
		while (i < j)
		{
			if (tmp < a[j])
			{
				j--;
			}
			else
			{
				a[i] = a[j];
				i++;
				break;
			}
		}
		while (i < j)
		{
			if (tmp >= a[i])
			{
				i++;
			}
			else
			{
				a[j] = a[i];
				j++;
				break;
			}
		}
	}
	a[i] = tmp;

	return i;
}

void quick_sort(int a[], int n)
{
	int ret;

	if (n == 1)
	{
		return;
	}

	ret = find(a, n);

	quick_sort(a, ret);
	quick_sort(a + ret + 1, n - ret - 1);
}

int main(int argc, char *argv[])
{
	int i;
	int len;

	int a[9] = {4, 1, 8, 2, 1, 9, 7, 3, 1};

	len = 9;

	quick_sort(a, len);

	for (i = 0; i < len; i++)
	{
		printf("%d ", a[i]);
	}
	printf("\n");

	return 0;
}
