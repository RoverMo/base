#include <stdio.h>
#include <malloc.h>

#define LEN 1024

struct mem_node
{
	size_t size;
	struct mem_node *next;
};

struct free_list
{
	void *first;
	struct mem_node mn;
};

struct free_list fl;

void init(void *p)
{
	fl.first = p;
	fl.mn.size = LEN;
	fl.mn.next = NULL;
}

void *my_malloc(size_t size)
{
	void *q = fl.first;
	struct free_list *temp = &fl;

	while (temp->mn.size < size + 24 && temp->mn.next != NULL)
	{
		temp = temp->mn.next;
	}

	if (temp->mn.next == NULL)
	{
		return NULL;
	}

	q = temp->first;
	q = (void *)((size_t)q + 24);

	temp->first = (void *)((size_t)temp->first + 24 + size);

	return q;
}

/*void free(void *p)
{
	size_t size2free = (size_t)(p - 16);
	void *nextp = (void *)((size_t)p + size2free);
}*/

int main(int argc, char *argv[])
{
	void *p = malloc(LEN);
	init(p);
	void *q = my_malloc(12);

	printf("%p", p);
	printf("%p", q);
	return 0;
}
