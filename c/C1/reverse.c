#include <stdio.h>

int reverse(int num)
{
	int temp;
	int result = 0;

	while (num)
	{
		result *= 10;
		temp = num % 10;
		num /= 10;
		result += temp;
	}

	return result;
}

int fun(int n)
{
	if (n * 9 == reverse(n))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int main()
{
	int i;

	for (i = 1000; i < 10000; i++)
	{
		if (fun(i))
		{
			printf("%d\n", i);
		}
	}
	printf("%d\n", reverse(12345));

	return 0;
}
