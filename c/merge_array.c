/*
 * 合并两个有序的数组，使之成位一个有序的数组
 */
#include <stdio.h>

void merge_array(int *a, size_t a_len, int *b, size_t b_len, int *c)
{
	while ((a_len != 0) && (b_len != 0))
	{
		if (*a < *b)
		{
			*c++ = *a++;
			a_len--;
		}
		else
		{
			*c++ = *b++;
			b_len--;
		}

		if (a_len == 0 && b_len != 0)
		{
			while (b_len)
			{
				*c++ = *b++;
				b_len--;
			}
		}
		if (b_len == 0 && a_len != 0)
		{
			while (a_len)
			{
				*c++ = *a++;
				a_len--;
			}
		}
	}
}

int main(int argc, char **argv)
{
	int a[] = {12, 56, 465};
	int b[] = {1, 13, 45};
	int c[6];
	int i;

	merge_array(a, 3, b, 3, c);

	printf("c = a + c\n");
	for (i = 0; i < 6; i++)
	{
		printf("%d\t", c[i]);
	}
	printf("\n");

	return 0;
}
