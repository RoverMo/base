#include <stdio.h>

#define N 5

void insertsort(int a[], int n)
{
	int b[N + 1];
	int i = 0, len = n, j = 0, k = 0, l = n;
	b[0] = a[0];
	while(len > 0)
	{
		while(b[j] < a[i + 1])
		{
			while( l > i)
			{
				a[l ] = a[l - 1];
				l--;
			}
			j++;
			i++;
		}
		len--;
	}
	while(k < n)
	{
		printf("%d ", a[k]);
		k++;
	}
}

int main()
{
	int a[N];
	insertsort(a, N);
	return 0;
}