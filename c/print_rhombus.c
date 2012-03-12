/*
 * 输出菱形
 */

#include <stdio.h>

void print_rhombus(int size)
{
	int len = size / 2 + 1;
	int i = 0, j = 0;
	int blen, pointlen;

	while(i < len)
	{
		blen = len - i - 1;
		pointlen = 2 * i + 1;
		while(blen > 0)
		{
			printf(" ");
			blen--;
		}
		while(pointlen > 0)
		{
			printf("*");
			pointlen--;
		}
		printf("\n");
		i++;
	}
	while(j < len - 1)
	{
		blen = j + 1;
		pointlen = size - 2 * j - 2;
		while(blen > 0)
		{
			printf(" ");
			blen--;
		}
		while(pointlen > 0)
		{
			printf("*");
			pointlen--;
		}
		printf("\n");
		j++;
	}
}

int main()
{
	print_rhombus(11);
	return 0;
}
