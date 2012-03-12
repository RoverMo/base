#include <stdio.h>
#include <malloc.h>

typedef struct device
{
	int devid;
	struct device *next;
}device_t;

typedef struct dev_list
{
	device_t *first;
}dev_list_t;

int init_dev(dev_list_t **list)
{
	*list = (dev_list_t *)malloc(sizeof(dev_list_t));
	if (list == NULL)
	{
		printf("malloc fail\n");
		return 0;
	}

	(*list)->first = NULL;

	return 1;
}

device_t *create(int id)
{
	device_t *p;

	p = (device_t *)malloc(sizeof(device_t));
	p->devid = id;
	p->next = NULL;

	return p;
}

void add_list(dev_list_t *list, device_t *dev)
{
	device_t *p = list->first;

	if (p != NULL)
	{
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = dev;
	}
	else
	{
		list->first = dev;
	}
}

int del_list(dev_list_t *list, int id)
{
	device_t *p = list->first;
	device_t *q;

	if (p == NULL)
	{
		return 0;
	}

	while (p->devid != id && p != NULL)
	{
		q = p;
		p = p->next;
	}

	if (p == list->first && p->devid == id)
	{
		list->first = list->first->next;
		free(p);
	}
	else
	{
		q->next = p->next;
		free(p);
	}

	return 1;
}

void reverse_list(dev_list_t *list)
{
	device_t *p, *q, *r;

	p = list->first;
	q = p->next;
	list->first->next = NULL;

	while(q != NULL)
	{
		r = q->next;
		q->next = p;
		p = q;
		q = r;
	}

	list->first = p;
}

device_t *reverse_list1(device_t *dev)
{
	device_t *p;

	if (dev->next != NULL)
	{
		p = reverse_list1(dev->next);
		dev->next->next = dev;
		dev->next = NULL;
		return p;
	}
	else
	{
		return dev;
	}
}

void reverse_print(dev_list_t *list)
{
	device_t *p = list->first;
	int a[20];
	int i = 0;

	while (p != NULL)
	{
		a[i] = p->devid;
		p = p->next;
		i++;
	}

	for(i = i - 1; i >= 0; i--)
	{
		printf("%d->", a[i]);
	}
	printf("NULL\n");
}

void reverse_print1(device_t *dev)
{
	if (dev != NULL)
	{
		reverse_print1(dev->next);
		printf("%d->", dev->devid);
	}
}

void print(dev_list_t *lst)
{
	device_t *p = lst->first;

	while (p != NULL)
	{
		printf("%d->", p->devid);
		p = p->next;
	}
	printf("NULL\n");
}

void destroy(dev_list_t *list)
{
	device_t *p = list->first;
	device_t *q;

	while (p != NULL)
	{
		q = p->next;
		free(p);
		p = q;
	}
	free(list);
}

int main(int argc, char *argv[])
{
	dev_list_t *lst;
	device_t *dev;
	int i;

	init_dev(&lst);
	for(i = 0; i < 10; i++)
	{
		dev = create(i);
		add_list(lst, dev);
	}
	del_list(lst, 0);
	del_list(lst, 9);
	del_list(lst, 5);
//	reverse_print1(lst->first);
//	printf("NULL\n");
	lst->first = reverse_list1(lst->first);
	print(lst);
	destroy(lst);

	return 0;
}
