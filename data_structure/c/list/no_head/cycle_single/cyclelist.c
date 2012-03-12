#include <stdio.h>
#include <malloc.h>
#include <linux/errno.h>

typedef int type_t;

struct node
{
	type_t data;
	struct node *next;
};

struct cycle_list
{
	struct node *first;
	struct node *last;

	struct node *(*alloc_node)(const type_t *data);
	int (*is_empty)(const struct cycle_list *list);
	void (*add_node)(struct cycle_list *list, struct node *new_node);
	int (*del_node)(struct cycle_list *list);
	void (*destory)(struct cycle_list *list);
};

static struct node *cycle_list_alloc_node(const type_t *data)
{
	struct node *new_node;

	new_node = (struct node *)malloc(sizeof(*new_node));
	if (NULL == new_node)
	{
		printf("create node failed\n");
		return NULL;
	}

	new_node->data = *data;
	new_node->next = NULL;

	return new_node;
}

static int cycle_is_empty(const struct cycle_list *list)
{
	return (list->first == NULL);
}

static void cycle_list_add_node(struct cycle_list *list, struct node *new_node)
{
	if (list->is_empty(list))
	{
		list->first = new_node;
		list->last	= new_node;
		new_node->next = list->first;

		return;
	}

	list->last->next = new_node;
	new_node->next = list->first;
	list->first = new_node;
}

static int cycle_list_del_node(struct cycle_list *list)
{
	struct node *tmp;

	if (list->is_empty(list))
	{
		printf("list is empty\n");

		return -1;
	}

	if (list->first == list->last)
	{
		free(list->first);
		list->first = NULL;
		list->last	= NULL;

		return 0;
	}

	tmp = list->first;
	list->last->next = tmp->next;
	list->first = tmp->next;

	free(tmp);

	return 0;
}

static void cycle_list_destory(struct cycle_list *list)
{
	while (!list->is_empty(list))
	{
		list->del_node(list);
	}

	free(list);
}

int cycle_list_init(struct cycle_list **new_list)
{
	*new_list = (struct cycle_list *)malloc(sizeof(**new_list));
	if (NULL == *new_list)
	{
		printf("create list failed\n");
		return -ENOMEM;
	}

	(*new_list)->first	= NULL;
	(*new_list)->last	= NULL;
	(*new_list)->alloc_node = cycle_list_alloc_node;
	(*new_list)->is_empty	= cycle_is_empty;
	(*new_list)->add_node	= cycle_list_add_node;
	(*new_list)->del_node	= cycle_list_del_node;
	(*new_list)->destory	= cycle_list_destory;

	return 0;
}

void josephy(size_t m, size_t n)
{
	int i;
	int ret;
	struct node *new_node;
	struct cycle_list *list;

	ret = cycle_list_init(&list);
	if (ret < 0)
	{
		printf("init cycle list failed\n");

		return;
	}

	for (i = m; i > 0; i--)
	{
		new_node = list->alloc_node(&i);
		if (new_node == NULL)
		{
			goto alloc_node_error;
		}
		list->add_node(list, new_node);
	}

	while (list->first != list->last)
	{
		for (i = 0; i < n - 1; i++)
		{
			list->last	= list->first;
			list->first = list->first->next;
		}
		printf("%d->", list->first->data);
		list->del_node(list);
	}

	printf("\nking:%d\n", list->first->data);

	list->destory(list);

	return;

alloc_node_error:
	list->destory(list);
}

int main(int argc, char *argv[])
{
	josephy(10, 3);

	return 0;
}
