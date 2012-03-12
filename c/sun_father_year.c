/*
 * 小红今年12岁，她父亲比她大20岁，编一程序，计算出她的父亲在几年后比她年龄
 * 大一倍。那时他们两人的年龄各为多少？
 */

#include <stdio.h>

int main(int argc, char *argv[])
{
	int i = 0;
	int year = 12;

	while(year * 2 != year + 20)
	{
		year++;
		i++;
	}

	printf("%d\n", i);

	return 0;
}
