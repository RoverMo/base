/*
 * 常用宏
 */

#include <stdio.h>

#define MIN(x, y) ((x) > (y) ? (y) : (x))
#define MAX(x, y) ((x) < (y) ? (y) : (x))

#define IS2POWER(num) (!((num) & ((num) - 1)))

#define SQURT(n) ((n) * (n))

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

#ifdef GCC
#define SWAP(x, y) do { \
						__typeof(x) tmp = (x); \
						(x) = (y); \
						(y) = (tmp); \
					} while (0)

#else
#define SWAP(x, y) do { \
						(x) = (x) ^ (y); \
						(y) = (x) ^ (y); \
						(x) = (x) ^ (y); \
					} while (0)
#endif

#define STR(x) #x

#define INIT(x, y) char *lib_##y##x = #x#y

#define DPRINT(fmt, args...) printf(fmt, ##args)

#define container_of(ptr, type, member) ((type *)((char *)ptr - (char *)(&((type *)0)->member)))

int main(int argc, char *argv[])
{
	int a = 1;
	int b = 65;

	SWAP(a, b);
	printf("a = %d\nb= %d\n", a, b);

	printf("hello"STR(12345)"\n");

	printf("MIN:%d\n", MIN(4, 5));

	INIT(11, x);
	puts(lib_x11);

	DPRINT("%s():%d\n", __func__, __LINE__);

	if (IS2POWER(1))
	{
		printf("yes\n");
	}
	else
	{
		printf("no\n");
	}

	return 0;
}
