/*
 * 请写出atoi函数的一个可移植版本。
 */

#include <stdio.h>

int atoi(const char *p)
{
	int num;
	int flag;

	num  = 0;
	flag = 1;

	if (*p == '-')
	{
		flag = -1;
		p++;
	}

	while (*p)
	{
		num *= 10;
		num += *p - '0';
		p++;
	}

	return num * flag;
}

int main(int argc, char *argv[])
{
	printf("%d\n", atoi("-12023"));

	return 0;
}
