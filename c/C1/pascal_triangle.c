#include <stdio.h>

int element(int line, int row)
{
	if (row == 0 || row == line)
	{
		return 1;
	}
	else
	{
		return element(line - 1, row - 1) + element(line - 1, row);
	}
}

void pascal_triangle(int total_line)
{
	int i, j;

	for (i = 0; i < total_line; i++)
	{
		for (j = 3; j < 3 * total_line - 3 * i; j++)
		{
			printf(" ");
		}

		for (j = 0; j < i + 1; j++)
		{
			printf("%6d", element(i, j));
		}
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	pascal_triangle(9);

	return 0;
}
