#include <stdio.h>
#include <malloc.h>

typedef struct tree_node* Type1;
typedef char Type2;

struct node
{
	Type1 data;
	struct node *next;
};

struct stack
{
	struct node *top;

	int (*is_empty)(const struct stack *s);
	void (*destory)(struct stack *s);
	int (*push)(struct stack *s, Type1 data);
	int (*pop)(struct stack *s, Type1 *data);
};

static int is_empty_stack(const struct stack *s)
{
	return (s->top == NULL);
}

static void destory_stack(struct stack *s)
{
	struct node *tmp;

	while (!is_empty_stack(s))
	{
		tmp = s->top;
		s->top = tmp->next;
		free(tmp);
	}
	free(s);
}

static int push_stack(struct stack *s, Type1 data)
{
	struct node *new_node;

	new_node = (struct node*)malloc(sizeof(*new_node));
	if (new_node == NULL)
	{
		return -1;
	}

	new_node->data = data;
	new_node->next  = s->top;

	s->top = new_node;

	return 0;
}

static int pop_stack(struct stack *s, Type1 *data)
{
	struct node *tmp;

	if (is_empty_stack(s))
	{
		return -1;
	}

	(*data) = s->top->data;

	tmp = s->top;
	s->top = s->top->next;

	free(tmp);

	return 0;
}

int init_stack(struct stack **s)
{
	(*s) = (struct stack *)malloc(sizeof(**s));
	if ((*s) == NULL)
	{
		return -1;
	}

	(*s)->top		= NULL;
	(*s)->is_empty	= is_empty_stack;
	(*s)->destory	= destory_stack;
	(*s)->push		= push_stack;
	(*s)->pop		= pop_stack;

	return 0;
}

struct queue
{
	struct node *front;
	struct node *rear;

	int (*is_empty)(struct queue *q);
	void (*destory)(struct queue *q);
	int (*enter)(struct queue *q, const Type1 d);
	int (*out)(struct queue *q, Type1 *d);
};

static int is_empty_queue(struct queue *q)
{
	return (q->front == NULL);
}

static void destory_queue(struct queue *q)
{
	struct node *tmp;

	while (!is_empty_queue(q))
	{
		tmp = q->front;
		q->front = tmp->next;
		free(tmp);
	}

	free(q);
}

static int enter_queue(struct queue *q, const Type1 d)
{
	struct node *new_node;

	new_node = (struct node *)malloc(sizeof(new_node));
	if (new_node == NULL)
	{
		return -1;
	}
	new_node->data = d;
	new_node->next = NULL;

	if (is_empty_queue(q))
	{
		q->rear = new_node;
		q->front = new_node;

		return 0;
	}

	q->rear->next = new_node;
	q->rear = new_node;

	return 0;
}

static int out_queue(struct queue *q, Type1 *d)
{
	struct node *tmp;

	if (is_empty_queue(q))
	{
		return -1;
	}

	(*d) = q->front->data;

	tmp = q->front;
	q->front = q->front->next;

	if (is_empty_queue(q))
	{
		q->rear = NULL;
	}

	free(tmp);

	return 0;
}

int init_queue(struct queue **q)
{
	(*q) = (struct queue *)malloc(sizeof(**q));
	if ((*q) == NULL)
	{
		return -1;
	}

	(*q)->front		= NULL;
	(*q)->rear		= NULL;
	(*q)->is_empty	= is_empty_queue;
	(*q)->destory	= destory_queue;
	(*q)->enter		= enter_queue;
	(*q)->out		= out_queue;

	return 0;
}

struct tree_node
{
	Type2 data;
	struct tree_node *child;
	struct tree_node *sibling;
};

struct tree
{
	struct tree_node *root;

	int (*create)(struct tree *t, const Type2 *str);
	void (*clean_up)(struct tree *t);
	void (*destory)(struct tree *t);
	void (*visit_node)(const struct tree_node *node);
	void (*root_first_traversal)(const struct tree *t);
	void (*root_last_traversal)(const struct tree *t);
	int (*width_traversal)(const struct tree *t);
	int (*depth_traversal)(const struct tree *t);
};

static int create_tree(struct tree *t, const Type2 *str)
{
	int ret;
	struct node *stack_node;
	struct stack *s;
	struct tree_node *new_node;
	struct tree_node *cur_root;
	struct tree_node *tmp;

	ret = init_stack(&s);
	if (ret < 0)
	{
		return -1;
	}

	if (*str == 0)
	{
		return 0;
	}

	new_node = (struct tree_node*)malloc(sizeof(*new_node));
	if (new_node == NULL)
	{
		return -1;
	}
	new_node->data = *str++;
	new_node->child = NULL;
	new_node->sibling = NULL;
	t->root = new_node;

	while (*str != 0)
	{
		switch (*str)
		{
		case '(' :
			s->push(s, new_node);
			break;

		case ')' :
			s->pop(s, &new_node);
			break;

		case ',' :
			break;

		default:
			new_node = (struct tree_node*)malloc(sizeof(*new_node));
			if (new_node == NULL)
			{
				return -1;
			}

			new_node->child = NULL;
			new_node->sibling = NULL;
			new_node->data = *str;

			stack_node = s->top;
			cur_root = stack_node->data;

			if (cur_root->child == NULL)
			{
				cur_root->child = new_node;
			}
			else
			{
				tmp = cur_root->child;
				while(tmp->sibling)
				{
					tmp = tmp->sibling;
				}
				tmp->sibling = new_node;
			}
		}

		str++;
	}

	return 0;
}

static void clean_up_node(struct tree_node *root)
{
	if (root != NULL)
	{
		clean_up_node(root->child);
		clean_up_node(root->sibling);
		free(root);
	}
}

static void clean_up_tree(struct tree *t)
{
	clean_up_node(t->root);
}

static void destory_tree(struct tree *t)
{
	t->clean_up(t);
	free(t);
}

static void visit(const struct tree_node *node)
{
	printf("%c ", node->data);
}

static void rf_traversal(const struct tree *t, const struct tree_node *root)
{
	if (root != NULL)
	{
		t->visit_node(root);
		rf_traversal(t, root->child);
		rf_traversal(t, root->sibling);
	}
}

static void root_first_traversal_tree(const struct tree *t)
{
	rf_traversal(t, t->root);
}

static void rl_traversal(const struct tree *t, const struct tree_node *root)
{
	if (root != NULL)
	{
		rf_traversal(t, root->child);
		rf_traversal(t, root->sibling);
		t->visit_node(root);
	}
}

static void root_last_traversal_tree(const struct tree *t)
{
	rl_traversal(t, t->root);
}

static int width_traversal_tree(const struct tree *t)
{
	int ret;
	struct tree_node *tmp;
	struct queue *q;

	ret = init_queue(&q);
	if (ret < 0)
	{
		return -1;
	}

	if (t->root != NULL)
	{
		ret = q->enter(q, t->root);
		if (ret < 0)
		{
			return -1;
		}
	}

	while (!is_empty_queue(q))
	{
		q->out(q, &tmp);
		t->visit_node(tmp);
		tmp = tmp->child;

		while(tmp)
		{
			ret = q->enter(q, tmp);
			if (ret < 0)
			{
				return -1;
			}
			tmp = tmp->sibling;
		}
	}

	q->destory(q);

	return 0;
}

static int depth_traversal_tree(const struct tree *t)
{
	int ret;
	struct tree_node *tmp;
	struct stack *s;

	ret = init_stack(&s);
	if (ret < 0)
	{
		return -1;
	}

	if (t->root != NULL)
	{
		ret = s->push(s, t->root);
		if (ret < 0)
		{
			return -1;
		}
	}

	while (!is_empty_stack(s))
	{
		s->pop(s, &tmp);
		t->visit_node(tmp);

		tmp = tmp->child;
		while(tmp)
		{
			ret = s->push(s, tmp);
			if (ret < 0)
			{
				return -1;
			}

			tmp = tmp->sibling;
		}
	}

	s->destory(s);

	return 0;
}

int init_tree(struct tree **t)
{
	(*t) = (struct tree *)malloc(sizeof(**t));
	if ((*t) == NULL)
	{
		return -1;
	}

	(*t)->root		= NULL;
	(*t)->create	= create_tree;
	(*t)->clean_up	= clean_up_tree;
	(*t)->destory	= destory_tree;
	(*t)->visit_node= visit;
	(*t)->root_first_traversal	= root_first_traversal_tree;
	(*t)->root_last_traversal	= root_last_traversal_tree;
	(*t)->width_traversal		= width_traversal_tree;
	(*t)->depth_traversal		= depth_traversal_tree;

	return 0;
}

int main(int argc, char *argv[])
{
	int ret;
	const char *str = "1(2(5,6),3,4(7,8,9))";
	struct tree *t;

	ret = init_tree(&t);
	if (ret < 0)
	{
		return -1;
	}

	ret = t->create(t, str);
	if (ret < 0)
	{
		return -1;
	}

	t->root_first_traversal(t);
	printf("\n");

	t->root_last_traversal(t);
	printf("\n");

	t->width_traversal(t);
	printf("\n");

	t->depth_traversal(t);
	printf("\n");

	t->destory(t);

	return 0;
}
