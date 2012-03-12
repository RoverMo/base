#include <stdio.h>
#include "string.h"
#include <string.h>

#define MAX_STR_LEN	64
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int main(int argc, char *argv[])
{
	// const char *src = "";
	// char dest[MAX_STR_LEN] = "cdg";
	// char *p;
	// int len;
	int ret;
	char a = 7;
	int b = 7;

	ret = memcmp(&a, &b, sizeof(a));

	printf("%d\n", ret);

	return 0;
}
