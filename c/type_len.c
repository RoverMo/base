#include <stdio.h>

#define PRINT_TYPE_LEN(type) (printf("%s : %ld\n", #type, sizeof(type)))

int main(int argc, char *argv[])
{
	PRINT_TYPE_LEN(char);
	PRINT_TYPE_LEN(void);
	printf("\n");

	PRINT_TYPE_LEN(short);
	printf("\n");

	PRINT_TYPE_LEN(int);
	PRINT_TYPE_LEN(float);
	printf("\n");

	PRINT_TYPE_LEN(long);
	PRINT_TYPE_LEN(double);
	PRINT_TYPE_LEN(long long);
	PRINT_TYPE_LEN(void *);
	printf("\n");

	PRINT_TYPE_LEN(long double);

	return 0;
}

