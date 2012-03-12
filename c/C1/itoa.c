#include <stdio.h>

void itoa(int num, char *ary)
{
	int temp = num;
	if (num < 0)
	{
		num = -num;
	}

	do {
		*ary++ = num % 10 + '0';
		num /= 10;
	} while (num);

	if (temp < 0)
		*ary++ = '-';
	*ary = '\0';
}

int str_len(const char *str)
{
	int len = 0;

	while (*str++ != '\0')
	{
		len++;
	}

	return len;
}

int main(int argc, char *argv[])
{
	char a[10];
	int i;

	itoa(0, a);
	for (i = str_len(a) -1; i > -1; i--)
	{
		printf("%c", a[i]);
	}
	printf("\n");

	return 0;
}
