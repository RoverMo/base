#include <stdio.h>

#define INTLEN	sizeof(int)

int intMax(int len)
{
	int intmax = 1;
	int i;
	for(i = len-1; i > 0; i--)
	{
		intmax *= 2;
	}
	return intmax - 1;
}

int notAddOne(int num)
{
	num ^= intMax(INTLEN * 8);
	num++;
	return num;
}

void toBin(int dec)
{
	int i = 0, flag = 0;
	int bin[INTLEN * 8] = {0};
	if(dec < 0)
	{
		bin[INTLEN * 8 - 1] = 1;
		dec *= -1;
		dec = notAddOne(dec);
	}
	do
	{
		bin[i] = dec % 2;
		dec /= 2;
		i++;
	}while(dec);
	for (i = INTLEN * 8 - 1; i >= 0; i--)
	{
		if(bin[i] == 1)
			flag = 1;
		if(flag == 1)
		{
			printf("%d", bin[i]);
			if(i % 8 == 0)
				printf(" ");
		}
	}
	printf("\n");
}

int main(void)
{
	int dec;
	printf("Please input a decimal number:");
	scanf("%d",&dec);
	printf("Binary is ");
	toBin(dec);
}
