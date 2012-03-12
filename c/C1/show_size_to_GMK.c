#include <stdio.h>

void show_size(size_t size)
{
	if (size >= 0 && size < 1023 )
		printf("%luB\n", size);
	else if (size >= 1024 && size < 1024 * 1024 - 1)
	{
		printf("%.2fK\n", size / 1024.0);
	}
	else if (size >= 1024 * 1024 && size < 1024 * 1024 * 1024 - 1)
	{
		printf("%.2fM\n", size / (1024 * 1024.0 - 1));
	}
	else
	{
		printf("%.2fG\n", size / (1024 * 1024 * 1024.0 -1));
	}
}

int main(int argc, char *argv[])
{
	show_size(104500000000);

	return 0;
}
