/*
 *	 打印出如下图案:
 *	 * 
 *	 *.*. 
 *	 *..*..*.. 
 *	 *...*...*...*... 
 *	 *....*....*....*....*.... 
 *	 *.....*.....*.....*.....*.....*..... 
 *	 *......*......*......*......*......*......*...... 
 *	 *.......*.......*.......*.......*.......*.......*.......*.......
 */

#include <stdio.h>

void printgraph(int n)
{
	int i, j, k;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j <= i; j++)
		{
			printf("*");
			for(k = 0; k < i; k++)
			{
				printf(".");
			}
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	printgraph(7);

	return 0;
}