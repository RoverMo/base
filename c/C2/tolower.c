/*
 *���ܣ����ַ�chת����Сд��ĸ
 *������ch����ĸ
 *����ֵ��chΪ��дʱ����ch��Сд��ĸ��chΪ����ʱ����ԭֵ
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