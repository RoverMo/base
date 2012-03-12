#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct data data_t;

struct data
{
	int id;
	char name[16];

	void (*print)(data_t *d);
};

struct list_node
{
	char DATA[0];
	data_t data;
	struct list_node *next;
};

void data_print(data_t *d)
{
	printf("%s:%d", d->name, d->id);
}

struct list
{
	struct list_node *first;

	int (*is_empty)(struct list *lst);
	int (*node_create)(struct list_node **new_node, const void *data, ssize_t n);
	void (*add_head)(struct list *lst, struct list_node *new_node);
	void (*add_tail)(struct list *lst, struct list_node *new_node);
	int (*del_head)(struct list *lst);
	int (*del_tail)(struct list *lst);
	int (*iterate_reverse)(struct list *lst);
	int (*recursion_reverse)(struct list *lst);
	void (*reverse_print)(struct list *lst);
	void (*print)(struct list *lst);
	void (*destroy)(struct list *lst);
};

static int list_is_empty(struct list *lst)
{
	return (lst->first == NULL);
}

static int list_node_create(struct list_node **new_node, const void *data, ssize_t n)
{
	(*new_node) = (struct list_node *)malloc(sizeof(**new_node));
	if (*new_node == NULL)
	{
		printf("Line %d malloc() fail\n", __LINE__);
		return -1;
	}
	memcpy((*new_node)->DATA, data, n);
	(*new_node)->next	= NULL;

	return 0;
}

static void list_add_head(struct list *lst, struct list_node *new_node)
{
	new_node->next	= lst->first;
	lst->first		= new_node;
}

static void list_add_tail(struct list *lst, struct list_node *new_node)
{
	struct list_node *tmp;

	tmp = lst->first;

	if (!lst->is_empty(lst))
	{
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = new_node;
	}
	else
	{
		lst->first = new_node;
	}
}

static int list_del_head(struct list *lst)
{
	struct list_node *tmp;

	if (lst->is_empty(lst))
	{
		return -1;
	}

	tmp = lst->first;
	lst->first = tmp->next;

	free(tmp);

	return 0;
}

static int list_del_tail(struct list *lst)
{
	struct list_node *tmp, *tail;

	if (lst->is_empty(lst))
	{
		return -1;
	}

	tmp		= lst->first;
	tail	= tmp;

	while (tail->next != NULL)
	{
		tmp = tail;
		tail = tail->next;
	}

	if (tmp != tail)
	{
		tmp->next = NULL;
		free(tail);
	}
	else
	{
		free(tail);
		lst->first = NULL;
	}

	return 0;
}

static int list_iterate_reverse(struct list *lst)
{
	struct list_node *p, *q, *r;

	if (lst->is_empty(lst))
	{
		return -1;
	}

	p = lst->first;
	q = p->next;
	lst->first->next = NULL;

	while(q != NULL)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}

	lst->first = p;

	return 0;
}

static struct list_node *__list_recursion_reverse(struct list_node *node)
{
	struct list_node *p;

	if (node->next != NULL)
	{
		p = __list_recursion_reverse(node->next);
		node->next->next = node;
		node->next = NULL;
		return p;
	}
	else
	{
		return node;
	}
}

static int list_recursion_reverse(struct list *lst)
{
	if (!lst->is_empty(lst))
	{
		lst->first = __list_recursion_reverse(lst->first);
		return 0;
	}

	return -1;
}

static void __list_reverse_print(struct list_node *node)
{
	if (node != NULL)
	{
		__list_reverse_print(node->next);
		node->data.print(&node->data);
		printf("->");
	}
}

static void list_reverse_print(struct list *lst)
{
	__list_reverse_print(lst->first);
	printf("NULL\n");
}

static void list_print(struct list *lst)
{
	struct list_node *tmp = lst->first;

	while (tmp != NULL)
	{
		tmp->data.print(&tmp->data);
		printf("->");
		tmp = tmp->next;
	}
	printf("NULL\n");
}

static void list_destroy(struct list *list)
{
	struct list_node *p, *q;

	p = list->first;

	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(list);
}

int init_list(struct list **lst)
{
	(*lst) = (struct list *)malloc(sizeof(**lst));
	if ((*lst) == NULL)
	{
		printf("malloc fail\n");
		return -1;
	}

	(*lst)->first		= NULL;
	(*lst)->is_empty	= list_is_empty;
	(*lst)->node_create = list_node_create;
	(*lst)->add_head	= list_add_head;
	(*lst)->add_tail	= list_add_tail;
	(*lst)->del_head	= list_del_head;
	(*lst)->del_tail	= list_del_tail;
	(*lst)->destroy		= list_destroy;
	(*lst)->print		= list_print;
	(*lst)->reverse_print		= list_reverse_print;
	(*lst)->iterate_reverse		= list_iterate_reverse;
	(*lst)->recursion_reverse	= list_recursion_reverse;

	return 0;
}

int main(int argc, char *argv[])
{
	struct list *lst;
	struct list_node *node;
	int i;
	data_t data;

	init_list(&lst);

	for(i = 10; i < 20; i++)
	{
		data.id		= i;
		data.name[0]= 'A' + i;
		data.name[1]= '\0';
		data.print	= data_print;
		lst->node_create(&node, &data, sizeof(data));
		lst->add_tail(lst, node);
	}
	lst->print(lst);

	for (i = 9; i > 0; i--)
	{
		data.id		= i;
		data.name[0]= 'A' + i;
		data.name[1]= '\0';
		data.print	= data_print;
		lst->node_create(&node, &data, sizeof(data));
		lst->add_head(lst, node);
	}
	lst->print(lst);

	lst->del_head(lst);
	lst->print(lst);

	lst->del_tail(lst);
	lst->print(lst);

	lst->reverse_print(lst);

	lst->iterate_reverse(lst);
	lst->print(lst);

	lst->recursion_reverse(lst);
	lst->print(lst);

	lst->destroy(lst);

	return 0;
}
