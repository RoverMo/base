/*
 * 打印出所有的“水仙花数”，所谓“水仙花数”是指一个三位数，其各位数字立方和等于该数本
 * 例如：153是一个“水仙花数”，因为153=1的三次方＋5的三次方＋3的
 */

#include <stdio.h>

#define X3(i) ((i) * (i) * (i))
#define VALUE(i, j, k) ((i) + 10 * (j) + 100 * (k))

int is_narcissus(int num)
{
	int i;
	int place[3];

	for (i = 0; i < 3; i++)
	{
		place[i] = num % 10;
		num /= 10;
	}

	if (X3(place[0]) + X3(place[1]) + X3(place[2]) == VALUE(place[0], place[1], place[2]))
	{
		return 1;
	}

	return 0;
}

int main()
{
	int i;

	for (i = 100; i < 1000; i++)
	{
		if (is_narcissus(i))
		{
			printf("%d\n", i);
		}
	}

	return 0;
}
