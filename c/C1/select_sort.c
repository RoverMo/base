#include <stdio.h>

#define LEN(a) sizeof(a) / sizeof(a[0])

typedef struct node{
	int num;
}node_t;

void select_sort(node_t a[], int len)
{
	int i;
	int j;
	int k;
	node_t temp;

	for (i = 0; i < len - 1; i++)
	{
		k = i;
		for (j = i + 1; j < len; j++)
		{
			if (a[k].num > a[j].num)
			{
				k = j;
			}
		}

		if (k > i)
		{
			temp = a[i];
			a[i] = a[k];
			a[k] = temp;
		}
	}
}

int main(int argc, char *argv[])
{
	int i;
	node_t a[]={{5}, {4}, {8}, {2}, {45}, {0}, {26}};

	select_sort(a, LEN(a));

	for(i = 0; i < LEN(a); i++)
	{
		printf("%d  ", a[i].num);
	}
	printf("\n");

	return 0;
}
