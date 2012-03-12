#include <stdio.h>

struct node
{
	int data;
	int index;
};

int get_count(int n)
{
	int i;

	for (i = 0; (1 << i) < n; i++);

	return (1 << (i + 1)) - 1;
}

int creat_tree(struct node **tree, int n)
{
	int ret;

	*tree = (struct node *)malloc(n * sizeof(**tree));
	if (*tree == NULL)
	{
		return -1;
	}

	memset(*tree, 0, n * sizeof(**tree));

	return 0;
}

void init_tree(struct node *tree, int a[], int len)
{
	int i;
	int n;

	n = get_count(len);

	for (i = 0; i < len; i++)
	{
		tree[i + n >> 1].data  = a[i];
		tree[i + n >> 1].index = 1;
	}
}

void competition_sort(int a[], int len)
{
	int i, j;
	int n;
	struct node *tree;

	n = get_count(len);
	creat_tree(&tree, n);
	init_tree(tree, a, n);
}

int main(int argc, char *argv[])
{
	return 0;
}
