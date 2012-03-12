/*
 * 十进制转十六进制
 */

#include <stdio.h>
#include <string.h>

#define SWAP(x, y) do { \
					__typeof(x) tmp = (x); \
					(x) = (y); \
					(y) = tmp; \
				} while(0)

void reverse_str(char *str, size_t len)
{
	int i;

	for(i = 0; i < len >> 1; i++)
	{
		SWAP(str[i], str[len - i - 1]);
	}
}

void dec2hex(unsigned int dec, char *hex)
{
	int i, temp;

	i = 0;
	memset(hex, 0, sizeof(hex));

	while(dec > 0)
	{
		temp = dec % 16;
		if(temp >= 10)
		{
			hex[i] = temp + 'A' - 10;
		}
		else
		{
			hex[i] = temp + '0';
		}

		dec /= 16;
		i++;
	}

	reverse_str(hex, i);
}

int main(int argc, char *argv[])
{
	char hex[10];
	unsigned int dec;

	scanf("%d", &dec);

	dec2hex(dec, hex);

	printf("hex = 0x%s\n", hex);

	return 0;
}
