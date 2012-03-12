/*
 * Çón!
 */

#include <stdio.h>

#ifdef REPETITION

unsigned long factorial(unsigned long n) // Ñ­»·
{
	unsigned long factorial = 1;
	while (n > 0)
	{
		factorial *= n;
		n--;
	}
	return factorial;
}

#else

unsigned long factorial(unsigned long n) // µÝ¹é
{
	if(n == 1)
	{
		return 1;
	}
	else
	{
		return n * factorial(n-1);
	}
}

#endif

int main(int argc, char *argv[])
{
	printf("%ld\n", factorial(6));

	return 0;
}


