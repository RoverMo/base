/*
 * 判断一个数是否为素数。
 */

#include <stdio.h>

int is_prime(unsigned int num)
{
	int i;

	for (i = 2; i * i < num; i++)
	{
		if (0 == num % i)
		{
			break;
		}
	}

	if (i * i > num)
	{
		return 1;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	unsigned int num;

	printf("%s", "num:");
	scanf("%d", &num);

	if (is_prime(num))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	return 0;
}
