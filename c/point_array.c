/*
 * 定义一个二维数组，存放一周七天的英文单词。分别用指针数组和数组指针二种
 * 方式，输出各个单词。
 */

#include <stdio.h>

#define MAX_POINT_ARRAY	8
#define MAX_STR_LEN		16
#define ARRAY_SIZE(a)	(sizeof(a) / sizeof(a[0]))

int main(int argc, char *argv[])
{
	int i;
	char str[][MAX_STR_LEN] = {"Monday", "Tuesday", "Wedesday", "Thuresday", "Friday", "Saturday", "Sunday"};
	char (*array_point)[MAX_STR_LEN];
	char *point_array[MAX_POINT_ARRAY];

	array_point = &str[0];

	printf("%s\n", *array_point);

	for (i = 0; i < ARRAY_SIZE(str); i++)
	{
		point_array[i] = str[i];
		printf("%s\n", str[i]);
	}

	return 0;
}
