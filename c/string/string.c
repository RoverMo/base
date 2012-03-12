#include <stddef.h>

size_t _strlen(const char *s)
{
	size_t len;

	for (len = 0; *s; s++, len++);

	return len;
}

int _strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 != *s2)
		{
			return *s1 - *s2;
		}
		s1++;
		s2++;
	}

	return 0;
}

int _strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		if (s1[i] != s2[i])
		{
			return s1[i] - s2[i];
		}
	}

	return 0;
}

int _memcmp(const void *s1, const void *s2, size_t n)
{
	size_t i;
	const unsigned char *ps1, *ps2;

	ps1 = (const unsigned char *)s1;
	ps2 = (const unsigned char *)s2;

	for (i = 0; i < n; i++)
	{
		if (ps1[i] != ps2[i])
		{
			return ps1[i] - ps2[i];
		}
	}

	return 0;
}

char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return (char *)s;
		}
		s++;
	}

	return NULL;
}

char *_strrchr(const char *s, int c)
{
	char *ret;

	ret = NULL;

	while (*s)
	{
		if (*s == c)
		{
			ret = (char *)s;
		}
		s++;
	}

	return ret;
}

char *_strchrnul(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
		{
			return (char *)s;
		}
		s++;
	}

	return NULL;
}

void *_memchr(const void *s, int c, size_t n)
{
	const unsigned char *str;

	str = (const unsigned char *)s;
	while (n)
	{
		if (*str == c)
		{
			return (void *)str;
		}
		str++;
		n--;
	}

	return NULL;
}

void *_memrchr(const void *s, int c, size_t n)
{
	const unsigned char *str;

	str = (const unsigned char *)s;
	while (n--)
	{
		if (str[n] == c)
		{
			return (void *)&str[n];
		}
	}

	return NULL;
}

char *_strstr(const char *haystack, const char *needle)
{
	int haystack_len;
	int needle_len;
	int ret;

	haystack_len	= _strlen(haystack);
	needle_len		= _strlen(needle);

	while (haystack_len >= needle_len)
	{
		if (*haystack == *needle)
		{
			ret = _strncmp(haystack + 1, needle + 1, needle_len - 1);
			if (ret == 0)
			{
				return (char *)haystack;
			}
		}

		haystack++;
		haystack_len--;
	}

	return NULL;
}

char *_strcpy(char *dest, const char *src)
{
	size_t i;

	for (i = 0; src[i]; i++)
	{
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return dest;
}

char *_strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i]; i++)
	{
		dest[i] = src[i];
	}

	for (; i < n; i++)
	{
		dest[i] = '\0';
	}

	return dest;
}

void *_memcpy(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *pdest;
	const unsigned char *psrc;

	pdest	= dest;
	psrc	= src;

	for (i = 0; i < n; i++)
	{
		pdest[i] = psrc[i];
	}

	return dest;
}

void *_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char *pdest;
	const unsigned char *psrc;

	pdest	= (unsigned char *)dest;
	psrc	= (const unsigned char *)src;

	while (n)
	{
		*pdest = *psrc;
		if (*pdest == c)
		{
			return ++pdest;
		}

		pdest++;
		psrc++;
		n--;
	}

	return NULL;
}

void *_memmove(void *dest, const void *src, size_t n)
{
	size_t i;
	unsigned char *pdest, *psrc;

	pdest	= (unsigned char *)dest;
	psrc	= (unsigned char *)src;

	if (pdest < psrc + n)
	{
		while (n--)
		{
			pdest[n] = psrc[n];
		}
	}
	else
	{
		for (i = 0; i < n; i++)
		{
			pdest[i] = psrc[i];
		}
	}

	return dest;
}

void *_memset(void *s, int c, size_t n)
{
	unsigned char *str;
	unsigned char ch;

	str	= (unsigned char *)s;
	ch	= (unsigned char)c;

	while (n--)
	{
		*str++ = ch;
	}

	return s;
}

char *_strcat(char *dest, const char *src)
{
	int i, j;

	for (i = 0; dest[i]; i++);

	for (j = 0; src[j]; j++, i++)
	{
		dest[i] = src[j];
	}

	dest[i] = '\0';

	return dest;
}

char *_strncat(char *dest, const char *src, size_t n)
{
	int i, j;

	for (i = 0; dest[i]; i++);

	for (j = 0; src[j] && j < n; i++, j++)
	{
		dest[i] = src[j];
	}
	for (; j < n; i++, j++)
	{
		dest[i] = '\0';
	}

	return dest;
}

size_t _strspn(const char *s, const char *accept)
{
	return 0;
}

size_t _strcspn(const char *s, const char *reject)
{
	size_t i, j;

	for (i = 0; s[i]; i++)
	{
		for (j = 0; reject[j]; j++)
		{
			if (s[i] == reject[j])
			{
				break;
			}
		}

		if (reject[j] == '\0')
		{
			break;
		}
	}

	return i;
}
