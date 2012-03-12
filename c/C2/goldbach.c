/*------------------------------------
题目：一个偶数总能表示为两个素数之和。
------------------------------------*/
#include <stdio.h>
#include <math.h>

void goldbach(int number)
{
	int prime1, prime2, i;
	//scanf("%d", &a);
	for(prime1 = 3; prime1 <= number / 2; prime1 += 2)
	{
		for(i = 2; i <= sqrt(prime1); i++)//找素数
		{
			if( prime1 % i == 0)
				break;
		}
		if(i > sqrt(prime1))//b为素数时，求偶数的补数d
			prime2 = number - prime1;
		else
			break;
		for(i = 2; i <= sqrt(prime2); i++)//判断d是否为素数
			if(prime2 % i == 0)
				break;
		if(i > sqrt(prime2))
		printf("%d=%d+%d\n", number, prime1, prime2);
	}
}

int main()
{
	goldbach(86);
	return 0;
}


