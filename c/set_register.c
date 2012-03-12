/*
 * 将地址为addr的内存的比特m到比特n位的值设置位val
 */

#include <stdio.h>

void set_register(unsigned long addr, size_t m, size_t n, unsigned long val)
{
	volatile unsigned long *value;

	value	= (volatile unsigned long *)addr;
	*value	&= ~(((1 << (n - m + 1)) - 1) << m);
	*value	|= val << m;
}

int main(int argc, char *argv[])
{
	int test;

	test = 0;

	set_register((unsigned long)&test, 1, 4, 0xF);
	printf("%X\n", test);

	return 0;
}
