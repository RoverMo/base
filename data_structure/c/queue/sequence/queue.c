#include <stdio.h>
#include <malloc.h>

typedef int data_t;

struct stack_node
{
	data_t data;
};

struct stack
{
	int top;
	int max;

	struct stack_node *elem;

	int (*create_node)(struct stack_node **new_node, const data_t *data);
	int (*is_empty)(struct stack *s);
	int (*is_full)(struct stack *s);
	int (*push)(struct stack *s, struct stack_node *new_node);
	int (*pop)(struct stack *s, struct stack_node *node);
	void (*destroy)(struct stack *s);
};

static int stack_create_node(struct stack_node **new_node, const data_t *data)
{
	*new_node = (struct stack_node *)malloc(sizeof(**new_node));
	if (*new_node == NULL)
	{
		return -1;
	}

	(*new_node)->data = *data;

	return 0;
}

static int stack_is_empty(struct stack *s)
{
	return s->top == 0;
}

static int stack_is_full(struct stack *s)
{
	return s->top == s->max;
}

static int stack_push(struct stack *s, struct stack_node *new_node)
{
	if (s->is_full(s))
	{
		return -1;
	}

	(s->elem)[s->top] = *new_node;

	s->top++;

	free(new_node);

	return 0;
}

static int stack_pop(struct stack *s, struct stack_node *node)
{
	if (s->is_empty(s))
	{
		return -1;
	}

	s->top--;
	*node = (s->elem)[s->top];

	return 0;
}

static void stack_destroy(struct stack *s)
{
	free(s->elem);
	free(s);
}

int stack_init(struct stack **s, ssize_t n)
{
	(*s) = (struct stack *)malloc(sizeof(**s));
	if (NULL == *s)
	{
		return -1;
	}

	(*s)->elem = malloc(n * sizeof(*(*s)->elem));
	if ((*s)->elem == NULL)
	{
		return -1;
	}

	(*s)->top = 0;
	(*s)->max = n;
	(*s)->create_node = stack_create_node;
	(*s)->is_empty	= stack_is_empty;
	(*s)->is_full	= stack_is_full;
	(*s)->push		= stack_push;
	(*s)->pop		= stack_pop;
	(*s)->destroy	= stack_destroy;

	return 0;
}

int main(int argc, char *argv[])
{
	struct stack *s;
	int ret;
	int i;
	struct stack_node *new_node;

	ret = stack_init(&s, 10);
	if (ret < 0)
	{
		return -1;
	}

	for (i = 0; i < 10; i++)
	{
		s->create_node(&new_node, &i);
		s->push(s, new_node);
	}

	for (i = 0; i < 10; i++)
	{
		s->pop(s, new_node);

		printf("%d->", new_node->data);
	}
	printf("NULL\n");

	return 0;
}
