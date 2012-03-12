/*
*��������gcm
*���ܣ������������Լ��
*������firstNumber��seconedNumberҪ�����Լ����������
*����ֵ�����������Լ��
*/

/*
*��������lcm
*���ܣ�����������󹫱���
*������firstNumber��seconedNumberҪ����󹫱�����������
*����ֵ����������󹫱���
*/

#include <stdio.h>

#ifdef REPETITION
unsigned int gcm(unsigned int firstNumber, unsigned int seconedNumber)
{
	int remainder;
	while (remainder = (firstNumber % seconedNumber))
	{
		firstNumber = seconedNumber;
		seconedNumber = remainder;
	}
	return seconedNumber;
}

#else

unsigned int gcm(unsigned int firstNumber, unsigned int seconedNumber)
{
	if(firstNumber % seconedNumber == 0)
	{
		return seconedNumber;
	}
	else
	{
		return gcm(seconedNumber,firstNumber%seconedNumber);
	}
}

#endif

unsigned int lcm(unsigned int firstNumber, unsigned int seconedNumber)
{
	return firstNumber * seconedNumber / gcm(firstNumber, seconedNumber);
}

int main(void)
{
	printf("%d\n", gcm(8, 12));
	printf("%d\n", lcm(8, 12));
	return 0;
}
