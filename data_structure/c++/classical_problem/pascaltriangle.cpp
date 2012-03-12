/*
 * 用队列输出杨辉三角
 */

#include <stdio.h>

struct node
{
	int data;
	node *link;
};

class queue
{
private:
	node *front;
	node *rear;
	int curr_len;
public:**
	queue();
	~queue(){};
	int en_queue(int elem);
	int de_queue(int *elem);
	int is_empty();
	int getfront(int *elem);
};

queue::queue()
{
	front = NULL;
	rear = NULL;
	curr_len = 0;
}

int queue::is_empty()
{
	return curr_len == 0;
}

int queue::en_queue(int elem)
{
	node *newnode;

	newnode = new node;
	if(newnode == NULL)
	{
		return -1;
	}
	newnode->data = elem;
	newnode->link = NULL;

	if (is_empty())
	{
		front = newnode;
		rear = newnode;
	}
	else
	{
		rear->link = newnode;
		rear = newnode;
	}
	curr_len++;

	return 0;
}

int queue::de_queue(int *elem)
{
	node *temp;

	if(is_empty())
	{
		return -1;
	}

	*elem = front->data;
	temp = front;
	front = front->link;
	delete temp;

	if (is_empty())
	{
		front = NULL;
		rear = NULL;
	}

	curr_len--;

	return 0;
}

int queue::getfront(int *elem)
{
	if (is_empty())
	{
		return -1;
	}

	*elem = front->data;

	return 0;
}

void pascaltriangle(int n)
{
	int temp, elem, item;
	queue q;
	int i, j, k;

	for (j = 0; j < 3 * n; j++)
	{
		printf(" ");
	}
	printf("%6d\n", 1);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < 3 * (n - i); j++)
		{
			printf(" ");
		}

		q.en_queue(1);
		printf("%3d", 1);
		for (k = 0; k < i; k++)
		{
			q.de_queue(&elem);
			q.getfront(&temp);
			item = elem + temp;
			q.en_queue(item);
			printf("%6d", item);
		}
		printf("%6d\n", 1);
	}
}

int main()
{
	queue q;
	int len = 10;
	int i;
	int elem;

	for (i = 0; i < len; i++)
	{
		q.en_queue(i);
	}

	for (i = 0; i < len; i++)
	{
		q.de_queue(&elem);
		printf("%d->", elem);
	}
	printf("NULL\n");

	pascaltriangle(5);

	return 0;
}
