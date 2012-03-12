/*
 * 杨辉三角
 */

#include <stdio.h>
#include <malloc.h>
#include <linux/errno.h>

struct pascal_triangle
{
	size_t line;
	size_t *elements;

	size_t (*get_element)(size_t line, size_t row);
	size_t (*get_element_count)(struct pascal_triangle *triangle);
	void (*print)(struct pascal_triangle *triangle);
	void (*destory)(struct pascal_triangle *triangle);
};

static size_t pascal_triangle_get_element(size_t line, size_t row)
{
	if (row == 0 || row == line)
	{
		return 1;
	}
	else
	{
		return pascal_triangle_get_element(line - 1, row - 1) + pascal_triangle_get_element(line - 1, row);
	}
}

static size_t pascal_triangle_get_element_count(struct pascal_triangle *triangle)
{
	return ((triangle->line * (1 + triangle->line)) >> 1);
}

static void pascal_triangle_print(struct pascal_triangle *triangle)
{
	int i, j;
	int index;

	index = 0;

	for (i = 0; i < triangle->line; i++)
	{
		for (j = 3; j < 3 * triangle->line - 3 * i; j++)
		{
			printf(" ");
		}

		for (j = 0; j < i + 1; j++)
		{
			printf("%6ld", triangle->elements[index]);
			index++;
		}
		printf("\n");
	}
}

static void pascal_triangle_destory(struct pascal_triangle *triangle)
{
	free(triangle->elements);
	free(triangle);
}

static void pascal_triangle_element_init(struct pascal_triangle *triangle)
{
	int i, j;
	static int index;

	index = 0;

	for (i = 0; i < triangle->line; i++)
	{
		for (j = 0; j <= i; j++)
		{
			(triangle->elements)[index] = triangle->get_element(i, j);
			index++;
		}
	}
}

int pascal_triangle_init(struct pascal_triangle **triangle, size_t n)
{
	(*triangle) = (struct pascal_triangle *)malloc(sizeof(**triangle));
	if (*triangle == NULL)
	{
		return -ENOMEM;
	}

	(*triangle)->line = n;
	(*triangle)->elements = (size_t *)malloc(((1 + n) * n * sizeof((*triangle)->elements)) >> 1);
	if ((*triangle)->elements == NULL)
	{
		return -ENOMEM;
	}
	(*triangle)->get_element		= pascal_triangle_get_element;
	(*triangle)->print				= pascal_triangle_print;
	(*triangle)->destory			= pascal_triangle_destory;
	(*triangle)->get_element_count	= pascal_triangle_get_element_count;
	pascal_triangle_element_init(*triangle);

	return 0;
}

int main(int argc, char *argv[])
{
	struct pascal_triangle *triangle;

	pascal_triangle_init(&triangle, 9);

	triangle->print(triangle);

	triangle->destory(triangle);

	return 0;
}
