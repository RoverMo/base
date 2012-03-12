#include <stdio.h>

struct B{
	int a;
	char b;
};

struct  A{
	int a;
	int b;
	short c;
	struct B sb;
};

int main()
{
	printf("%lu \n", sizeof(struct A));

	return 0;
}
