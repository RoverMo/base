/*
 *���ܣ���chת���ɴ�д��ĸ
 *������ch��Ҫת������
 *����ֵ��chΪСд��ĸ�Ƿ�����Ӧ��д��ĸ�����򷵻�ԭֵ
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
