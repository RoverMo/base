#include <stdio.h>

int main()
{
	int f1, f2;
	int i;

	f1 = f2 = 1;
	for (i = 1; i <= 10; i++)
	{
		printf("%d, %d, ", f1, f2);
		if (i % 5 == 0)
			printf("\n");

		f1 = f1 + f2;
		f2 = f1 + f2;
	}

	return 0;
}
