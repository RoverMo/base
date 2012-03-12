#include <stdio.h>
#include <malloc.h>
#include <linux/errno.h>

enum triangle_type
{
	EQUILATERAL,
	SCALENE,
	ISOSCELES,
	ILLEGAL,
};

struct triangle
{
	size_t side[3];
	int type;

	size_t (*get_side_len)(void);
	void (*free)(struct triangle *);
};

static int triangle_alloc(struct triangle **trg)
{
	(*trg) = (struct triangle *)malloc(sizeof(**trg));
	if (NULL == (*trg))
	{
		return -ENOMEM;
	}

	return 0;
}

static size_t triangle_get_side_len(void)
{
	int num;

	scanf("%d",&num);
	while((num < 1) || (num > 200))
	{
		printf("It is wrong,please input again:");
		getchar();
		scanf("%d",&num);
	}
	return num;
}

static void triangle_free(struct triangle *trg)
{
	free(trg);
}

static int triangle_init(struct triangle *trg, int a, int b, int c)
{
	trg->side[0] = a;
	trg->side[1] = b;
	trg->side[2] = c;

	if ((a >= b+c) || (b >= a+c) || (c >= a+b))
	{
		trg->type = ILLEGAL;

		return -EINVAL;
	}
	else if ((a == b) && (b == c))
	{
		trg->type = EQUILATERAL;
	}
	else if ((a != b) && (b != c) && (a != c))
	{
		trg->type = SCALENE;
	}
	else
	{
		trg->type = ISOSCELES;
	}

	trg->free = triangle_free;

	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	size_t a, b, c;
	struct triangle *trg;

	ret = triangle_alloc(&trg);
	if (ret < 0)
	{
		return ret;
	}

	printf("Side A is :");
	a = triangle_get_side_len();
	printf("Side B is :");
	b = triangle_get_side_len();
	printf("Side C is :");
	c = triangle_get_side_len();
	printf("\nThe three sides are %lu,%lu,%lu\n", a, b, c);

	ret = triangle_init(trg, a, b, c);
	if (ret < 0)
	{
		printf("It is not a triangle\n");
		return ret;
	}

	switch (trg->type)
	{
		case ILLEGAL:
			printf("It is not a triangle\n");
			break;

		case SCALENE:
			printf("It is a scalene triangle\n");
			break;

		case EQUILATERAL:
			printf("It is an equilateral triangle\n");
			break;

		case ISOSCELES:
			printf("It is an isosceles triangle\n");
	}

	trg->free(trg);

	return 0;
}
