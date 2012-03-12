#include <stdio.h>
#include <malloc.h>

#define CONTAINER(ptr, type, member) ((struct type *)((void *)ptr - (void *)&((struct type*)0)->member))

typedef int type_t;

enum dev
{
	MEMERY = 1,
	KEY,
	NET
};

struct node
{
	struct node *next;
	type_t type;
};

struct list
{
	struct node *head;
};

struct mem_node
{
	struct node link;
	int size;
};

struct key_node
{
	struct node link;
	char ch;
};

struct net_node
{
	struct node link;
	int model;
};

static int init_list(struct list **l)
{
	*l = (struct list *)malloc(sizeof(struct list));
	if (l == NULL)
	{
		return -1;
	}

	(*l)->head = NULL;

	return 0;
}

static void *create_node(void *pnode)
{
	struct node *pn = (struct node *)pnode;
	struct mem_node *mp = NULL;
	struct key_node *kp = NULL;
	struct net_node *np = NULL;
	void *p;

	switch (pn->type)
	{
		case MEMERY :
			mp = (struct mem_node *)malloc(sizeof(struct mem_node));
			mp->size = ((struct mem_node *)pnode)->size;
			mp->link.type = ((struct mem_node *)pnode)->link.type;
			mp->link.next = ((struct mem_node *)pnode)->link.next;
			p = mp;

			break;

		case KEY :
			kp = (struct key_node *)malloc(sizeof(struct key_node));
			kp->ch = ((struct key_node *)pnode)->ch;
			kp->link.type = ((struct key_node *)pnode)->link.type;
			kp->link.next = ((struct key_node *)pnode)->link.next;
			p = kp;

			break;

		case NET :
			np = (struct net_node *)malloc(sizeof(struct net_node));
			np->model = ((struct net_node *)pnode)->model;
			np->link.type = ((struct net_node *)pnode)->link.type;
			np->link.next = ((struct net_node *)pnode)->link.next;
			p = np;

			break;
	}

	return p;
}

static void list_add(struct list *l, struct node *n)
{
	struct node *p = l->head;

	if (p != NULL)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = n;
	}
	else
	{
		l->head = n;
	}
}

static int list_del(struct list *l, int n)
{
	int i;
	struct node *p = l->head;
	struct node *q;

	if (l == NULL)
	{
		return -1;
	}

	if (1 == n)
	{
		l->head = l->head->next;
		free(p);

		return 0;
	}

	for (i = 0; i < n - 2; i++)
	{
		p = p->next;
	}
	q = p->next;
	p->next = q->next;
	free(q);

	return 0;
}

static int print(struct list *l)
{
	struct node *p = l->head;
	struct mem_node *m;
	struct key_node *k;
	struct net_node *n;

	while (p != NULL)
	{
		switch (p->type)
		{
		case MEMERY :
			m = (struct mem_node *)CONTAINER(p, mem_node, link);
			printf("%d->", m->size);
			break;

		case KEY :
			k = (struct key_node *)CONTAINER(p, key_node, link);
			printf("%c->", k->ch);
			break;

		case NET :
			n = (struct net_node *)CONTAINER(p, net_node, link);
			printf("%d->", n->model);
			break;

		default :
			printf("ERROR\n");
			return -1;
		}
		p = p->next;
	}

	printf("NULL\n");

	return 0;
}

int main()
{
	struct list *l;
	int i;

	struct mem_node *mn;
	struct mem_node new_m = {.link.type = MEMERY, .link.next = NULL, .size = 512};

	struct key_node *kn;
	struct key_node new_k = {.link.type = KEY, .link.next = NULL, .ch = 'A'};

	struct net_node *nn;
	struct net_node new_n = {.link.type = NET, .link.next = NULL, .model = 123};

	init_list(&l);

	mn = (struct mem_node *)create_node((void *)&new_m);
	list_add(l, &(mn->link));

	kn = (struct key_node *)create_node((void *)&new_k);
	list_add(l, &(kn->link));

	nn = (struct net_node *)create_node((void *)&new_n);
	list_add(l, &(nn->link));

	print(l);

	return 0;
}
