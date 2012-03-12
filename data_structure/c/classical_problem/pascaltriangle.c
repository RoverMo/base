/*
 *用队列实现打印杨辉三角。
 */

#include <stdio.h>
#include <malloc.h>

struct node
{
	int data;
	struct node *link;
};

struct link_queue
{
	struct node *front;
	struct node *rear;
	int current_len;
};

void init_link_queue(struct link_queue *queue)
{
	queue->front = NULL;
	queue->rear  = NULL;
	queue->current_len = 0;
}

int is_empty(struct link_queue *queue)
{
	return !(queue->current_len);
}

int add_node(struct link_queue *queue, int data)
{
	struct node *newnode;

	newnode = (struct node*)malloc(sizeof(*newnode));
	if (newnode == NULL)
	{
		perror("malloc failed");
		return -1;
	}

	newnode->data = data;
	newnode->link = NULL;

	if (queue->front == NULL)
	{
		queue->front = newnode;
		queue->rear	 = newnode;
	}
	else
	{
		queue->rear->link = newnode;
		queue->rear       = newnode;
	}
	queue->current_len++;

	return 0;
}

int del_node(struct link_queue *queue, int *elem)
{
	struct node *temp;

	if (is_empty(queue))
	{
		printf("queue was empty");
	}

	*elem = queue->front->data;

	temp = queue->front;
	queue->front = queue->front->link;
	free(temp);

	if (is_empty(queue))
	{
		queue->front = NULL;
		queue->rear  = NULL;
	}

	queue->current_len--;

	return 0;
}

int getfront(struct link_queue *queue, int *elem)
{
	if (is_empty(queue))
	{
		return -1;
	}

	*elem = queue->front->data;

	return 0;
}

int print_node(struct link_queue *queue)
{
	struct node *elem;

	if (is_empty(queue))
	{
		return -1;
	}

	elem = queue->front;

	while (elem)
	{
		printf("%d ", elem->data);
		elem = elem->link;
	};

	return 0;
}

void pascaltriangle(int n)
{
	int i, j;
	int temp, elem, item;
	struct link_queue queue;

	init_link_queue(&queue);

	for (i = 0; i < n; i++)
	{
		printf("   ");
	}
	printf("%6d\n", 1);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n - i; j++)
		{
			printf("   ");
		}

		add_node(&queue, 1);
		printf("%3d", 1);

		for (j = 0; j < i; j++)
		{
			del_node(&queue, &elem);
			getfront(&queue, &temp);
			item = elem + temp;
			add_node(&queue, item);
			printf("%6d", item);
		}
		printf("%6d", 1);
#if 0
		printf("\t\t\t\t");
		print_node(&queue);
#endif
		printf("\n");
	}
}

int main(int argc, char *argv[])
{
	int i;
	int elem;
	struct link_queue queue;

	init_link_queue(&queue);

	for (i = 0; i < 10; i++)
	{
		add_node(&queue, i);
	}

	for (i = 0; i < 10; i++)
	{
		del_node(&queue, &elem);
		printf("%d->", elem);
	}
	printf("NULL\n");

	pascaltriangle(6);

	return 0;
}
