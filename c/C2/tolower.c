/*
 *功能：将字符ch转换成小写字母
 *参数：ch：字母
 *返回值：ch为大写时返回ch的小写字母，ch为其他时返回原值
 */

#include <stdio.h>

int tolower(int ch)
{
	if((ch >= 'A') && (ch <= 'Z'))
	{
		return ch + 32;
	}
	else
	{
		return ch;
	}
}

int main(void)
{
	char ch;
	scanf("%c", &ch);
	printf("%c\n", tolower(ch));
	return 0;
}