#include <stdio.h>
#include <malloc.h>

typedef int data_t;

struct stack_node
{
	data_t data;
	struct stack_node *next;
};

struct stack
{
	struct stack_node *top;

	int (*create_node)(struct stack_node **node, const data_t *data);
	int (*is_empty)(const struct stack *s);
	void (*push)(struct stack *s, struct stack_node *node);
	int (*pop)(struct stack *s, struct stack_node *node);
	void (*print)(const struct stack *s);
	void (*destory)(struct stack *s);
};

static int stack_create_node(struct stack_node **new_node, const data_t *data)
{
	*new_node = (struct stack_node *)malloc(sizeof(**new_node));
	if (NULL == *new_node)
	{
		return -1;
	}

	(*new_node)->data = *data;
	(*new_node)->next = NULL;

	return 0;
}

static int stack_is_empty(const struct stack *s)
{
	return (s->top == NULL);
}

static void stack_push(struct stack *s, struct stack_node *node)
{
	if (!s->is_empty(s))
	{
		node->next = s->top;
	}
	s->top = node;
}

static int stack_pop(struct stack *s, struct stack_node *node)
{
	struct stack_node *tmp;

	if (s->is_empty(s))
	{
		return -1;
	}

	tmp = s->top;
	*node = *tmp;
	s->top = tmp->next;
	free(tmp);

	return 0;
}

static void stack_print(const struct stack *s)
{
	struct stack_node *tmp;

	tmp = s->top;

	while(tmp)
	{
		printf("%d->", tmp->data);
		tmp = tmp->next;
	}
	printf("NULL\n");
}

static void stack_destory(struct stack *s)
{
	struct stack_node *tmp;

	while (s->top != NULL)
	{
		tmp = s->top;
		s->top = s->top->next;
		free(tmp);
	}
}

int stack_init(struct stack **new_stack)
{
	(*new_stack) = (struct stack *)malloc(sizeof(**new_stack));
	if (NULL == *new_stack)
	{
		return -1;
	}

	(*new_stack)->top = NULL;
	(*new_stack)->create_node	= stack_create_node;
	(*new_stack)->is_empty		= stack_is_empty;
	(*new_stack)->push			= stack_push;
	(*new_stack)->pop			= stack_pop;
	(*new_stack)->print			= stack_print;
	(*new_stack)->destory		= stack_destory;

	return 0;
}

int main(int argc, char *argv[])
{
	int i;
	int ret;
	struct stack *s;
	struct stack_node *new_node, node;

	ret = stack_init(&s);
	if (ret < 0)
	{
		printf("Line %d stack_init() fail\n", __LINE__);
		return -1;
	}

	for (i = 0; i < 8; i++)
	{
		ret = s->create_node(&new_node, &i);
		if (ret < 0)
		{
			return ret;
		}
		s->push(s, new_node);
	}
	s->print(s);

	s->pop(s, &node);
	s->print(s);

	s->destory(s);

	return 0;
}
