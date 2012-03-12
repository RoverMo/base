/*
*���ܣ��Ȳ��������
*������firstArithmeticProgression���Ȳ���������
*	   numberOfProgression������
*	   tolerance:����
*����ֵ���Ȳ�����֮��
*/

#include <stdio.h>

#define FORMULA

typedef double type;

#ifdef FORMULA

type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//ʹ�ù�ʽ
{
	type lastArithProgre = firstArithProgre + tolerance * (numberOfProgre - 1);
	return  (firstArithProgre + lastArithProgre) * numberOfProgre / 2;
}
#endif

#ifdef REPETITION
type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//ʹ��ѭ��
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
type sumOfArithProgre(type firstArithProgre, int numberOfProgre, type tolerance)//ʹ�õݹ�
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
