#include <stdio.h>

int show_size(char *str)
{
	float temp = 0;
	float tmp = 0.1;
	int result;
	int flag = 1;

	while (1)
	{
		if(*str == '.')
		{
			flag = 0;
			str++;
			continue;
		}

		if (*str == 'K' || *str == 'M' || *str == 'G')
			break;

		if (flag)
		{
			temp *= 10;
			temp += *str - '0';
		}
		else
		{
			temp += (*str - '0') * tmp;
			tmp /= 10;
		}

		str++;
	}

	if (*str == 'K')
		result = temp * 1024;
	else if (*str == 'M')
		result = temp * 1024 * 1024;
	else
		result = temp * 1024 * 1024 * 1024;

	return result;
}

int main(int argc, char *argv[])
{
	int size;

	size = show_size("1M");
	printf("%d\n", size);

	return 0;
}
