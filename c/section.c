/*
 * 各段的地址及默认值
 */

#include <stdio.h>
#include <malloc.h>

unsigned int bss1;
static unsigned int bss2;
static unsigned int bss3 = 0;
const static unsigned int bss4;

const static unsigned int rodata1 = 1;
const unsigned int rodata2 = 2;

unsigned int data1 = 3;
static unsigned int data2 = 4;

int main(int argc, char *argv[])
{
	unsigned int *tmp;

	unsigned int stack1;
	const unsigned int stack2;

	unsigned int *heap1;
	const unsigned int *heap2;

	static unsigned int bss5;
	static unsigned int bss6 = 0;
	const static unsigned int bss7;

	static unsigned int data3 = 8;

	printf("stack:\n");
	printf("stack1\t%u\t%p\n", stack1, &stack1);
	printf("stack2\t%u\t%p\n", stack2, &stack2);
	printf("\n");

	stack1 = 9;
	tmp = (unsigned int *)&stack2;
	*tmp = 9;

	printf("stack1\t%u\t%p\n", stack1, &stack1);
	printf("stack2\t%u\t%p\n", stack2, &stack2);
	printf("\n");

	printf("heap:\n");
	printf("heap1:\t%u\t%p\n", *heap1, heap1);
	printf("heap2:\t%s\t%p\n", "EINVAL", heap2);
	printf("\n");

	heap1 = (unsigned int *)malloc(sizeof(heap1));
	heap2 = (const unsigned int *)malloc(sizeof(heap2));
	*heap1 = 10;
	tmp = (unsigned int *)heap2;
	*tmp = 10;

	printf("heap1:\t%u\t%p\n", *heap1, heap1);
	printf("heap2:\t%u\t%p\n", *heap2, heap2);
	printf("\n");

	printf("bss:\n");
	printf("bss1\t%u\t%p\n", bss1, &bss1);
	printf("bss2\t%u\t%p\n", bss2, &bss2);
	printf("bss3\t%u\t%p\n", bss3, &bss3);
	printf("bss4\t%u\t%p\n", bss4, &bss4);
	printf("bss5\t%u\t%p\n", bss5, &bss5);
	printf("bss6\t%u\t%p\n", bss6, &bss6);
	printf("bss7\t%u\t%p\n", bss7, &bss7);
	printf("\n");

	bss1 = 5;
	bss2 = 5;
	bss3 = 5;
	tmp  = (unsigned int *)&bss4;
	*tmp = 5;
	bss5 = 5;
	bss6 = 5;
	tmp  = (unsigned int *)&bss7;
	*tmp = 5;

	printf("bss1\t%u\t%p\n", bss1, &bss1);
	printf("bss2\t%u\t%p\n", bss2, &bss2);
	printf("bss3\t%u\t%p\n", bss3, &bss3);
	printf("bss4\t%u\t%p\n", bss4, &bss4);
	printf("bss5\t%u\t%p\n", bss5, &bss5);
	printf("bss6\t%u\t%p\n", bss6, &bss6);
	printf("bss7\t%u\t%p\n", bss7, &bss7);
	printf("\n");

	printf("data:\n");
	printf("data1\t%u\t%p\n", data1, &data1);
	printf("data2\t%u\t%p\n", data2, &data2);
	printf("data3\t%u\t%p\n", data3, &data3);
	printf("\n");

	data1 = 7;
	data2 = 7;
	data3 = 7;

	printf("data1\t%u\t%p\n", data1, &data1);
	printf("data2\t%u\t%p\n", data2, &data2);
	printf("data3\t%u\t%p\n", data3, &data3);
	printf("\n");

	printf("rodata:\n");
	printf("rodata1\t%u\t%p\n", rodata1, &rodata1);
	printf("rodata2\t%u\t%p\n", rodata2, &rodata2);

	// can not been reassign
#if 0
	tmp	 = (unsigned int *)&rodata1;
	*tmp = 6;
	tmp	 = (unsigned int *)&rodata2;
	*tmp = 6;

	printf("rodata1\t%u\t%p\n", rodata1, &rodata1);
	printf("rodata1\t%u\t%p\n", rodata2, &rodata2);
	printf("\n");
#endif

	return 0;
}
