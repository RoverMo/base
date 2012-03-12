/*
 *功能：将ch转换成大写字母
 *参数：ch：要转换的数
 *返回值：ch为小写字母是返回相应大写字母，否则返回原值
 */
#include <stdio.h>

int toupper(int ch)
{
	if((ch >= 'a') && (ch <= 'z'))
	{
		return ch - 'a' + 'A';
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
	printf("%c\n", toupper(ch));
	return 0;
}
