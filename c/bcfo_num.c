/*
 *功能：统计字母、数字、空格及其他的个数
 *参数：字符串
 *返回值：bcfo结构体
 */

#include <stdio.h>
#include <string.h>

struct bcfo
{
    unsigned int blank;
    unsigned int alpha;
    unsigned int figure;
    unsigned int other;
};

void count_bcfo(const char *str, struct bcfo *count)
{
	memset(count, 0, sizeof(*count));

    while (*str)
	{
		if (*str == ' ')
        {
			count->blank++;
        }
		else if ((*str >= 'a' && *str <= 'z') || (*str >= 'A' && *str <= 'Z'))
        {
			count->alpha++;
        }
		else if(*str >= '0' && *str <= '9')
        {
			count->figure++;
        }
		else
        {
			count->other++;
        }

		str++;
	}
}

int main(int argc, char **argv)
{
    struct bcfo number;

	const char *str = "jslsldlc../082mcs";

	count_bcfo(str, &number);

    printf("blank=%d,char=%d,figure=%d,other=%d\n", number.blank, number.alpha, number.figure, number.other);

    return 0;
}
