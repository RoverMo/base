#include <stdio.h>

#define LEN(a) (sizeof((a)) / sizeof((a)[0]))

void modified_insert_sort(int a[], int n, int delta)
{
	int i, j;
	int temp;

	for (i = delta; i < n; i += delta)
	{
		for (j = i; j >= delta; j -= delta)
		{
			if (a[j] < a[j - delta])
			{
				temp = a[j];
				a[j] = a[j - delta];
				a[j - delta] = temp;
			}
			else
				break;
		}
	}
}

void modified_insert_sort1(int a[], int n, int delta)
{
	int i, j;
	int temp;

	for (i = delta; i < n; i += delta)
	{
		temp = a[i];

		for (j = i - delta; j >= 0; j -= delta)
		{
			if (a[j] > temp)
				a[j + delta] = a[j];
			else
				break;
		}
		a[j + delta] = temp;
	}
}

void shell_sort(int a[], int n)
{
	int delta;
	int i;

	for (delta = n / 2; delta > 0; delta /= 2)
	{
		for (i = 0; i < delta; i++)
			modified_insert_sort1(&a[i], n - i, delta);
	}
}

void shell_sort(int a[], int len)
{
	int i, j;
	int delta;

	for (delta = len >> 1; delta > 0; delta >>= 1)
	{
	}

}

int main(int argc, char *argv[])
{
	int i;
	int a[] = {88, 6, 1, 9, 4, 1, 45, 21};

	shell_sort(a, LEN(a));

	for(i = 0; i < LEN(a); i++)
		printf("%d ", a[i]);
	printf("\n");

	return 0;
}
