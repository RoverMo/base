#include <stdio.h>

struct A
{
	char t;
	char k;
	unsigned long i;
	unsigned short m;
};

int main()
{
	printf("sizeof(A) = %lu\n", sizeof(struct A));

	return 0;
}
