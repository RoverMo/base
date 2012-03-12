/*
 * 枚举类型
 */

#include <stdio.h>
#include <linux/errno.h>

#define MAX_STR_LEN	16

enum week{
	MONDAY = 1, // default 0
	TUESDAY,	// TUESDAY = MONDAY + 1
	WEDNESDAY,
	THURESDAY,
	FRIDAY,
	SATURDAY,
	SUNDAY
};

int show_week(int n)
{
	char week[][MAX_STR_LEN] = {"Monday", "Tuesday", "Wedesday", "Thuresday", "Friday", "Saturday", "Sunday"};

	if (n > 7 || n < 1)
	{
		return -EINVAL;
	}

	printf("%s\n", week[n - 1]);

	return 0;
}

int main(int argc, char *argv[])
{
	show_week(SUNDAY);

	return 0;
}
