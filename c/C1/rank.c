#include <stdio.h>

/*int rank(int n)
{
	if (n == 1)
	{
		return 1;
	}
	else
	{
		return n * rank(n - 1);
	}
}*/

int rank(int n)
{
	int result = 1;

	while (n > 1)
	{
		result *= n;
		n--;
	}

	return result;
}

int rank_sum(int n)
{
	int sum = 0;
	int nrank = 1;
	int i;
	int j;

	for (i = 1; i < n + 1; i++)
	{
		nrank *= i;
		sum += nrank;
	}

	return sum;
}

int main()
{
	printf("%d\n", rank(3));
	printf("%d\n", rank_sum(3));

	return 0;
}
