/*
 * 显示状态
 */

#include <stdio.h>

void show_status(void)
{
	while(1)
	{
		printf("\\\r");
		printf("|\r");
		printf("/\r");
		printf("-\r");
		printf("\\\r");
	}
}

int main()
{
	show_status();

	return 0;
}
