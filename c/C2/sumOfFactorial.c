/*
 *���ܣ���1��+2��+3��+����+n��
 *������n
 *����ֵ�����ʽֵ֮
 */


#include <stdio.h>

long factorial(long n)
{
    if(n == 1)
    {
        return 1;
    }
    else
    {
        return n * factorial(n - 1);
    }
}

long sumOfFactorial(long n)
{
    if(n == 1)
    {
        return factorial(1);
    }
    else
    {
        return factorial(n) + sumOfFactorial(n - 1);
    }
}

int main(void)
{
    printf("%ld", sumOfFactorial(4));
    return 0;
}
