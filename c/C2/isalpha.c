/*
 *���ܣ��ж�ch�Ƿ�����ĸ
 *������chҪ�жϵ���ĸ
 *����ֵ��1.��ĸ��1
 *         2.����ĸ��0
 */

#include <stdio.h>

int isalpha(int ch)
{
    if (ch >= 'A' && ch <= 'Z' || ch >= 'a' && ch <= 'z')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    if(isalpha('a'))
    {
        printf("Yes\n");
    }
    else
    {
        printf("No\n");
    }
    return 0;
}
