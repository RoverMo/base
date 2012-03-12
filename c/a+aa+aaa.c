/*
 * 求sn=a+aa+aaa+…+aaa…a的值。例如当a=2,n=4时，sn=2+22+222+2222。
 * a和n由键盘输入。
 */

#include <stdio.h>

int sum_cycle(int a, int n)
{
	int i;
	int sum = 0;
	int temp = 0;

	for (i = 0; i < n; i++)
	{
		temp *= 10;
		temp += a;
		sum += temp;
	}

	return sum;
}

int main(int argc, char *argv[])
{
	int a, n;

	printf("a = ");
	scanf("%d", &a);

	printf("n = ");
	scanf("%d", &n);

	printf("%d\n", sum_cycle(a, n));

	return 0;
}
