/*
*功能：求1/x-1/(x+1)+1/(x+2)-1/(x+3)+……+1/(n-1)-1/n
*参数：begin：x
*	   n：n
*返回值：1/x-1/(x+1)+1/(x+2)-1/(x+3)+……+1/(n-1)-1/n之和
*/

#include <stdio.h>

/*double recip_sum(int begin, int n)
{
	double sum = 0;
	double sign = begin;
	while (n > 0)
	{
		sign = 1 / sign;
		sum += sign;
		sign = 1 / sign;
		sign > 0 ? sign++ : sign--;
		sign = sign * (-1);
		n--;
	}
	return sum;
}*/

double recip_sum(int begin, int n)
{
	double result	= 0;
	double temp		= n;
	double i		= begin;

	while (i < 2 * (n / 2))
	{
		result += 1 / i - 1 / (i + 1);
		i++;
	}

	if(n % 2 == 1)
	{
		result += 1 / temp;
	}
	return result;
}

int main()
{
	printf("%f\n", recip_sum(1, 3));
	return 0;
}
