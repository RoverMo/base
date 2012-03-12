/*
 * 输入一个华氏温度，输出摄氏温度，公式为：c=(5/9)*(f-32),输入前要有信息
 * 提示！输出结果保留两位小数点！
 */

#include <stdio.h>

#define FAHRE2CENTIG(f) (5 * ((f) - 32) / 9.0)

int main(int argc, char *argv[])
{
	float c;
	int f;

	printf("Please input a c tempuriture:");
	scanf("%d", &f);

	c = FAHRE2CENTIG(f);

	printf("f tempuruture: %.2f\n", c);

	return 0;
}
