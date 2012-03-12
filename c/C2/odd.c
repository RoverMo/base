/*--------------------------
题目：求m-n所能组成的奇数个数
备注：题目有问题，未指定组成的数的位数
修改：加上条件位数为m+1～n+1位
---------------------------*/
#include <stdio.h> 

long odd(int start, int end)
{
	long sum = 0, s;
	int j;
	int number = end - start + 1;
	for(j = start; j <= end; j++)
	{
		if(j % 2 == 1)
			sum++;
	}
	s = sum;
	for(j = 2; j <= number; j++)/*j is place of number*/
	{ 
		//printf("\n%ld", sum);
		if(start == 0 && j <= 2)
			s *= (number -1);
		else
			s *= number;
		sum += s;
	}
	return sum;
}
 
int main(void)
{
	printf("%ld\n", odd(1, 2));
	return 0;
} 
