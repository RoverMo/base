#include <stdio.h>

#define __CUSTOM__ __attribute__((section(".custom_section")))

#define INSTALL_APPLICATION(app_name, app_main) \
static const __USED__ __CUSTOM__ struct custom_sec_struct __custom_##app_name = { \
			.name = #app_name, \
			.main = app_main, \
}

#if __GNUC__ == 3 && __GNUC_MINOR__ >= 3 || __GNUC__ >= 4
#define __USED__    __attribute__((__used__))
#else
#define __USED__    __attribute__((__unused__))
#endif

struct custom_sec_struct
{
	const char *name;
	int (*main)(void);
};

extern const struct custom_sec_struct custom_sec_begin[], custom_sec_end[];

static int test(void)
{
	printf("%s@%s():%d\n", __FILE__, __FUNCTION__, __LINE__);

	return 0;
}

INSTALL_APPLICATION(test1, test);
INSTALL_APPLICATION(test2, test);
INSTALL_APPLICATION(test3, test);

int main(int argc, char *argv[])
{
	const struct custom_sec_struct *cs;

	for (cs = custom_sec_begin; cs < custom_sec_end; cs++)
	{
		printf("%s():%d\n", __FUNCTION__, __LINE__);
		cs->main();
	}

	return 0;
}
