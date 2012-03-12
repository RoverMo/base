/*
 *将一个正整数分解质因数。例如：输入165,打印出165=1*3*5*11.
 */

#include <stdio.h>

#define ABS(a) ((a) > 0 ? (a) : -(a))

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

void prime_mul(unsigned int num)
{
	unsigned int i;

	printf("%u = 1", num);

	i = 2;

	while (i <= num)
	{
		if (is_prime(i) && num % i == 0)
		{
			printf(" * %d", i);
			num /= i;
		}
		else
		{
			i++;
		}
	}
}

int main(int argc, char **argv)
{
	int num, b = 1;

	printf("Please input a number:");

	while (b)
	{
		scanf("%d",&num);
		if (num > 0)
		{
			b = 0;
		}
		else
		{
			printf("The number must bigger than 0!!\nPlease input again:");
		}
	};

	prime_mul(num);

	printf("\n");

	return 0;
}
