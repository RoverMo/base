/*
 * 约瑟夫环
 */

#include <stdio.h>
#include <malloc.h>
#include <linux/errno.h>

typedef struct node
{
	int data;
	struct node *next;
}node_t;

node_t *creat_list(int n)
{
	node_t *head;
	node_t *p;
	node_t *q;
	int i = 1;

	head = (node_t *)(malloc(sizeof(node_t)));
	head->data = i;
	p = head;

	while (i < n)
	{
		i++;
		q = (node_t *)(malloc(sizeof(node_t)));
		q->data = i;
		p->next = q;
		p = q;
	}

	q->next = head;

	return head;
}

void print_node(node_t *head)
{
	node_t *p = head;

	do {
		printf("%5d", p->data);
		p = p->next;
	} while(p != head);
	printf("\n");
}

node_t *node_del(node_t *node)
{
	node_t *bfnode;

	bfnode = node;

	if (node->next == node)
	{
		free(node);
		return NULL;
	}
	else
	{
		while(bfnode->next != node)
		{
			bfnode = bfnode->next;
		}

		bfnode->next = node->next;
		free(node);

		return bfnode->next;
	}
}

void josephus(int m, int n)
{
	int i = n;
	node_t *list = creat_list(m);
	printf("create %d nodes\n", m);

	while (list != list->next)
	{
		while(--i)
		{
			list = list->next;
		}

		printf("%d out\n", list->data);
		list = node_del(list);
		i = n;
	}

	printf("%d\n", list->data);
}

int main()
{
	josephus(10, 3);

	return 0;
}
