/*
 *����:���ַ���������룬�ܳ�Ϊkey������ÿ���ַ�����key��������z/Z��ᵽa/A
 *������str��ԭ���ַ���
 *		key���ܳ�
 *����ֵ�����ܺ���ַ���
 */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *encrypt(char str[], int key)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (isalpha(str[i]))
		{
			str[i] += key;
			if ((str[i] > 'z') || (str[i] > 'Z' && str[i] < 'a'))
			{
				str[i] -= 26;
			}
		}
		i++;
	}
	return str;
}

int main(int argc, char *argv[])
{
	char ch[] = "chinaCHINA.,.,.,";
	printf("%s\n",encrypt(ch, 4));

	return 0;
}
