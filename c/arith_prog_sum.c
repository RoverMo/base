/*
*功能：等差数列求和
*参数：firstArithmeticProgression：等差数列首项
*	   numberOfProgression：项数
*	   tolerance:公差
*返回值：等差数列之和
*/

#include <stdio.h>

#define FORMULA

typedef double type;

#ifdef FORMULA

type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//使用公式
{
	type lastArithProgre = firstArithProgre + tolerance * (numberOfProgre - 1);
	return  (firstArithProgre + lastArithProgre) * numberOfProgre / 2;
}
#endif

#ifdef REPETITION
type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//使用循环
{
	type sumOfArithProgre = 0;
	while (numberOfProgre > 0)
	{
		sumOfArithProgre += firstArithProgre;
		firstArithProgre += tolerance;
		numberOfProgre--;
	}
	return sumOfArithProgre;
}
#endif

#ifdef RECURSION
type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//使用递归
{
	if (numberOfProgre == 0)
	{
		return 0;
	}
	else
	{
		return firstArithProgre + sumOfArithProgre(firstArithProgre + tolerance, numberOfProgre - 1, tolerance);
	}
}
#endif

int main(void)
{
	printf("%lf\n", sumOfArithProgre(0.1, 100, 0.1));
	return 0;
}
