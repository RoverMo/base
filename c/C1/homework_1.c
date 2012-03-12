#include <stdio.h>
#include <malloc.h>

typedef struct node
{
	int data;
	struct node *next;
}node_t;

typedef struct list
{
	node_t *first;
}list_t;

struct stack_node
{
	int s_node;
	struct stack_node *link;
};

struct stack
{
	struct stack_node *top;
};

int init_list(list_t **lst)
{
	node_t *head;

	(*lst) = (list_t *)malloc(sizeof(list_t));
	if (lst == NULL)
	{
		printf("malloc fail\n");
		return 0;
	}

	head = (node_t *)malloc(sizeof(node_t));
	if (head == NULL)
	{
		printf("malloc fail\n");
		return 0;
	}

	head->next = NULL;

	(*lst)->first = head;

	return 1;
}

node_t *create(int id)
{
	node_t *p;

	p = (node_t *)malloc(sizeof(node_t));
	p->data = id;
	p->next = NULL;

	return p;
}

void add_list(list_t *lst, node_t *nd)
{
	node_t *p = lst->first;

	while (p->next != NULL)
	{
		p = p->next;
	}
	p->next = nd;
}

void print(list_t *lst)
{
	node_t *p = lst->first->next;

	while (p != NULL)
	{
		printf("%d->", p->data);
		p = p->next;
}
	printf("NULL\n");
}

void init_stack(struct stack *s)
{
	s->top = NULL;
}

int push(struct stack *s, int item)
{
	struct stack_node *temp = (struct stack_node *)malloc(sizeof(struct stack_node));
	if (temp == NULL)
	{
		return 0;
	}

	temp->s_node = item;
	temp->link = s->top;
	s->top = temp;

	return 1;
}

int pop(struct stack *s, int *elem)
{
	struct stack_node *snd;

	if (s->top == NULL)
	{
		return 0;
	}

	snd = s->top;
	*elem = s->top->s_node;

	s->top = s->top->link;
	free(snd);

	return 1;
}

void list2stack(list_t *lst, struct stack *s)
{
	node_t *l_nd = lst->first->next;
	while (l_nd != NULL)
	{
		push(s, l_nd->data);
		l_nd = l_nd->next;
	}
}

int main(int argc, char *argv[])
{
	list_t *lst;
	node_t *nd;
	struct stack s;
	int i;
	int id;

	init_list(&lst);
	for(i = 0; i < 10; i++)
	{
		nd = create(i);
		add_list(lst, nd);
	}
	print(lst);
	list2stack(lst, &s);

	for (i = 0; i < 10; i++)
	{
		pop(&s, &id);
		printf("%d->", id);
	}
	printf("NULL\n");

	return 0;
}
