/*
 * 两个乒乓球队进行比赛，各出三人。甲队为a,b,c三人，乙队为x,y,z三人。由抽
 * 签决定比赛名单。有人向队员打听比赛的名单。a说他不和x比，c说他不和x,z比
 * ，请编程序找出三队赛手的名单。
 */

#include <stdio.h>

void player()
{
	char a, b, c;
	int i, j, k;

	for (i = 'x'; i <= 'z'; i++)
	{
		a = i;

		if (a == 'x')
			continue;

		for (j = 'x'; j <= 'z'; j++)
		{
			if (a == j)
				continue;
			else
				b = j;

			for (k = 'x'; k <= 'z'; k++)
			{
				if (a == k || b == k)
					continue;
				else
					c = k;

				if (c == 'x' || c == 'z')
					continue;
			}
		}
	}

	printf("a:\t%c\nb:\t%c\nc:\t%c\n", a, b, c);
}

int main(int argc, char *argv[])
{
	player();

	return 0;
}
