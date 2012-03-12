/*
 * 开方
 */

#include <stdio.h>

#define ABS(n) ((n) > 0 ? (n) : (-(n)))

double sqrt(double num)
{
	double temp, e = 1;
	temp = num;

	while (e > 0.000001)
	{
		temp = 0.5 * (temp + num / temp);
		e = ABS(num - temp * temp);
	}
	return temp;
}

int main(int argc, char *argv[])
{
	double num;

	printf("num:");
	scanf("%lf", &num);

	printf("%f\n", sqrt(num));

	return 0;
}
