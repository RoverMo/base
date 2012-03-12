/*
 * 数组反转
 */

#include <stdio.h>

typedef int type_t;

#define SWAP(x, y) do { \
					__typeof(x) tmp = (x); \
					(x) = (y); \
					(y) = tmp; \
				} while(0)

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

void reverse(type_t *str, size_t len)
{
	int i;

	for(i = 0; i < len >> 1; i++)
	{
		SWAP(str[i], str[len - i - 1]);
	}
}

int main(int argc, char *argv[])
{
	int i;
	size_t len;
	type_t a[] = {1, 2, 3, 4, 5};

	len = ARRAY_SIZE(a);

	for (i = 0; i < len; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");

	reverse(a, len);

	for (i = 0; i < len; i++)
	{
		printf("%d\t", a[i]);
	}
	printf("\n");


	return 0;
}
