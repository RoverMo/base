#include <malloc.h>
#include "in.h"

#define CIP_LEN		32
#define BITS_INT	16

uint32_t htonl(uint32_t hostlong)
{
	int i;
	uint32_t netlong;

	netlong = 0;

	for (i = 0; i < 4; i++)
	{
		netlong |= (hostlong & 0xFF) << (24 - i * 8);
		hostlong >>= 8;
	}

	return netlong;
}

uint32_t ntohl(uint32_t netlong)
{
	return htonl(netlong);
}

uint16_t htons(uint16_t hostshort)
{
	uint16_t netshort;

	netshort = 0;

	netshort |= (hostshort & 0xFF) << 8;
	netshort |= (hostshort >> 8) & 0xFF;

	return netshort;
}

uint16_t ntohs(uint16_t netshort)
{
	return htons(netshort);
}

unsigned int aton(const char *a)
{
	unsigned int n;
	int scale;

	n = 0;
	scale = 10;

	if (*a == '0')
	{
		a++;
		if ((*a == 'x') || (*a == 'X'))
		{
			a++;
			scale = 16;
		}
		else
		{
			scale = 8;
		}
	}

	while (*a)
	{
		n += (*a - '0');
		if (*(a + 1))
		{
			n *= scale;
		}
		a++;
	}

	return n;
}

int inet_aton(const char *cp, struct in_addr *inp)
{
	int i, j;
	char *p, *q;
	int dot_num;
	unsigned int tmp;
	char str[CIP_LEN];

	j = 0;
	p = str;
	q = str;
	dot_num = 0;
	inp->s_addr = 0;

	while (*cp)
	{
		if (*cp == '.')
		{
			dot_num++;
		}
		str[j++] = *cp;
		cp++;
	}
	str[j] = '\0';

	if (dot_num > 3)
	{
		return -1;
	}

	for (i = 0; i < dot_num; i++)
	{
		p = q;
		while (*p != '.')
		{
			p++;
		}
		*p = '\0';
		tmp = aton(q);
		if (tmp > 1 << 8)
		{
			return -1;
		}
		inp->s_addr |= tmp << (i * 8);
		q = p + 1;
	}

	tmp = aton(q);
	if (tmp > 1 << ((4 - dot_num) * 8))
	{
		return -1;
	}

	if (dot_num == 1)
	{
		tmp = htonl(tmp);
		tmp >>= 8;
	}
	else if (dot_num == 2)
	{
		tmp = htons(tmp);
	}

	inp->s_addr |= (tmp << dot_num * 8);

	return 0;
}

in_addr_t inet_addr(const char *cp)
{
	struct in_addr addr;

	inet_aton(cp, &addr);

	return addr.s_addr;
}

char *ntoa(unsigned int n)
{
	int i;
	unsigned char *a;
	unsigned char ch[BITS_INT];

	i = 0;

	while (n)
	{
		ch[i++] = n % 10 + '0';
		n /= 10;
	}

	a = (unsigned char *)malloc(i);
	if (a == NULL)
	{
		return a;
	}

	while (i > 0)
	{
		i--
		a++ = ch[i];
	}
	*a = '\0';

	return a;
}

char *inet_ntoa(struct in_addr in)
{
	int i, j;
	char *aip;
	char *p;
	int tmp;
	char ch[BITS_INT];

	j = 0;
	aip = (char *)malloc(CIP_LEN);
	if (aip == NULL)
	{
		return aip;
	}
	p = aip;

	for (i = 0; i < 4; i++)
	{
		tmp = in.s_addr & 0xFF;
		while (tmp)
		{
			ch[j] = tmp % 10 + '0';
			tmp /= 10;
			j++;
		}

		while (j > 0)
		{
			j--;
			*p++ = ch[j];
		}
		*p++ = '.';
	}

	*(p - 1) = '\0';

	return aip;
}
