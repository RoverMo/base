#include <stdio.h>

void *mymemcpy(void *dest, const void *src, size_t n)
{
	char *p, *q;
	int i = n;

	p = (char *)dest;
	q = (char *)src;
	if (dest < src + n)
	{
		p += n;
		q += n;
		while (i > 0)
		{
			*p-- = *q--;
			i--;
		}
	}
	else
	{
		while (i > 0)
		{
			i--;
			*p++ = *q++;
		}
	}

	return dest;
}

int main()
{
	int dest[10];
	int src[5] = {1, 2, 3, 4, 5};
	int i = 0;	

	mymemcpy((void *)dest, (void *)src, sizeof(src));
	for (; i < 5; i++)
		printf("%d", dest[i]);
	printf("\n");

	return 0;
}
