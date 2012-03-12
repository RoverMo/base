/*
 * 变餐函数
 */

#include <stdio.h>

int max(int fmt, ...)
{
	int *p = &fmt;
	int i;
	int max = *(++p);

	p	= &fmt;
	max	= *(++p);

	for (i = 0; i < fmt; i++)
	{
		if (max > *(++p))
		{
			max = *p;
		}
	}

	return max;
}

int main(int argc, char *argv[])
{
	printf("%d\n", max(2, 0, 1));

	return 0;
}
