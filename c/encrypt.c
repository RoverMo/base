/*
 *功能:将字符串译成密码，密匙为key，即将每个字符加上key，若超过z/Z则会到a/A
 *参数：str：原文字符串
 *		key：密匙
 *返回值：加密后的字符串
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
