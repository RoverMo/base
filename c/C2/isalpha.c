/*
 *功能：判断ch是否是字母
 *参数：ch要判断的字母
 *返回值：1.字母：1
 *         2.非字母：0
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
