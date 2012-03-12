/*
 * 一位百万富翁遇到一陌生人，陌生人找他谈一个换钱计划，该计划如下：我每天给你十万元
 * ，而你第一天只需给我一分钱，第二天我仍给你十万元，你给我二分钱，第三天我仍给你十
 * 万元，你给我四分钱…你每天给我的钱是前一天的两倍，直到满一个月（30天），百万富翁
 * 很高兴，欣然接受了这个契约。请编写一个程序计算这一个月中陌生人给了百万富翁多少钱
 * ，百万富翁给陌生人多少钱。
 */

#include <stdio.h>

void rich_pool()
{
	int pool_play = 1000000;
	int rich_play = 1;
	int total_rich = 0;
	int total_pool = 0;
	int i;

	for (i = 0; i < 30; i++)
	{
		total_pool += pool_play;
		total_rich += rich_play;
		rich_play <<= 1;
	}

	printf("richtotal:%d\n", total_rich);
	printf("pooltotal:%d\n", total_pool);
}

int main(int argc, char *argv[])
{
	rich_pool();

	return 0;
}
