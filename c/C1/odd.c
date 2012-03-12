#include <stdio.h>

void odd(int *a, int from, int to)
{
	for (;from < to; from++)
	{
		if (from % 2)
		{
			*a++ = from;
		}
	}
}

int main()
{
	int a[50];
	int i;

	odd(a, 1, 100);
	for(i = 0; i < 50; i++)
	{
		printf("%d ", a[i]);
	}
}
