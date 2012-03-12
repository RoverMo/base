#include <stdio.h>
#include <malloc.h>

typedef int data_t;

struct queue_node
{
	data_t data;
	struct queue_node *next;
};

struct queue
{
	struct queue_node *front;
	struct queue_node *rear;

	int (*create_node)(struct queue_node **new_node, const data_t *data);
	int (*is_empty)(const struct queue *qu);
	void (*enter)(struct queue *qu, struct queue_node *new_node);
	int (*out)(struct queue *qu, struct queue_node *node);
	void (*print)(const struct queue *qu);
	void (*destroy)(struct queue *qu);
};

static int queue_create_node(struct queue_node **new_node, const data_t *data)
{
	(*new_node) = (struct queue_node *)malloc(sizeof(**new_node));
	if (NULL == *new_node)
	{
		return -1;
	}

	(*new_node)->data = *data;
	(*new_node)->next = NULL;

	return 0;
}

static int queue_is_empty(const struct queue *qu)
{
	return (qu->front == NULL);
}

static void queue_enter(struct queue *qu, struct queue_node *new_node)
{
	if (qu->is_empty(qu))
	{
		qu->front	= new_node;
		qu->rear	= new_node;
	}
	else
	{
		qu->rear->next	= new_node;
		qu->rear		= new_node;
	}
}

static int queue_out(struct queue *qu, struct queue_node *node)
{
	struct queue_node *tmp;

	if (qu->is_empty(qu))
	{
		return -1;
	}

	tmp = qu->front;
	*node = *tmp;
	qu->front = tmp->next;
	free(tmp);

	return 0;
}

static void queue_print(const struct queue *qu)
{
	struct queue_node *tmp;

	tmp = qu->front;
	while (tmp)
	{
		printf("%d->", tmp->data);
		tmp = tmp->next;
	}

	printf("NULL\n");
}

static void queue_destroy(struct queue *qu)
{
	struct queue_node *tmp;

	while (!qu->is_empty(qu))
	{
		tmp = qu->front;
		qu->front = tmp->next;
		free(tmp);
	}
}

int queue_init(struct queue **qu)
{
	(*qu) = (struct queue *)malloc(sizeof(**qu));
	if (NULL == *qu)
	{
		return -1;
	}

	(*qu)->front	= NULL;
	(*qu)->rear		= NULL;
	(*qu)->create_node	= queue_create_node;
	(*qu)->enter	= queue_enter;
	(*qu)->out		= queue_out;
	(*qu)->is_empty	= queue_is_empty;
	(*qu)->print	= queue_print;
	(*qu)->destroy	= queue_destroy;

	return 0;
}

int main(int argc, char *argv[])
{
	struct queue *qu;
	struct queue_node *new_node;
	struct queue_node node;
	int ret;
	int i;

	ret = queue_init(&qu);
	if (ret < 0)
	{
		printf("Line %d queue_init() failed\n", __LINE__);
		return ret;
	}

	for (i = 0; i < 8; i++)
	{
		qu->create_node(&new_node, &i);
		qu->enter(qu, new_node);
	}
	qu->print(qu);

	qu->out(qu, &node);
	qu->print(qu);

	qu->destroy(qu);

	return 0;
}
