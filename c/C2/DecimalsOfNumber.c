/*
 *���ܣ���number�ĸ���λ��ֵ��ŵ�����a��
 *������number��a[]
 *����ֵ:void
 */

#include <stdio.h>

void DecimalsOfNumber(int number, int a[10])
{
    int i = 0;
    while (number > 0)
    {
        a[i] = number % 10;
        number /= 10;
        i++;
    } 
}


int main()
{
    int a[10];
    int i = 0;
    DecimalsOfNumber(646353312,a);
    while (a[i])
    {
        printf("%d", a[i]);
        i++;
    }
    printf("\n");
    return 0;
}
