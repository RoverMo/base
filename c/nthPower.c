/*------------------------------
求x的n次方
------------------------------*/

#include <stdio.h>

#define ABS(n) ((n) > 0 ? (n) : -(n))

#if 0
//递归
double nthPower(int x, int n)
{
	double result;
	int absn;

	result = 1;
	absn = ABS(n);

	if(x == 0)
	{
		return 1;
	}
	else if(absn <= 0)
	{
		return result;
	}
	else
	{
		result = x * nthPower(x, absn - 1);
	}

	if(n > 0)
	{
		return result;
	}
	else
	{
		return 1 / result;
	}
}

#else
//循环
double nthPower(int x, int n)
{
	double result;
	int absn;

	result	= 1;
	absn	= ABS(n);

	if(x == 0 || absn == 0)
	{
		return 1;
	}
	else
	{
		for(; absn > 0; absn--)
		{
			result *= x;
		}
	}

	if(n > 0)
	{
		return result;
	}
	else
	{
		return 1/result;
	}
}
#endif

int main(void)
{
	printf("%lf\n",nthPower(2, -2));

	return 0;
}
