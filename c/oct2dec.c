/*-------------------------------
八进制转换为十进制
-------------------------------*/

#include <stdio.h>

int oct2dec(const char *oct)
{
	int dec = 0;

	while (*(oct) != '\n')
	{
		dec = dec * 8 + *oct - '0';
		oct++;
	}

	return dec;
}

int main(int argc, char *argv[])
{
	char oct[6];
	int i;
	int dec;

	i = 0;
	while((oct[i++] = getchar()) != '\n');

	dec = oct2dec(oct);
	oct[--i] = '\0';
	printf("0x%s = %d\n", oct, dec);

	return 0;
}
