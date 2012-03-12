#include <stdio.h>

template <class Type> class SingleList;

template <class Type>
class Node
{
	friend class SingleList<Type>;
private:
	Type data;
	Node *next;

public:
	Node(){}
	Node(const Type &d):next(NULL){data = d;}
	virtual ~Node(){};
	Type getData(){return data;}
};

template <class Type>
class SingleList
{
private:
	class Node<Type> *first;

public:
	SingleList():first(NULL){}
	~SingleList();

	int createNode(Node<Type> **newNode, const Type &data);

	int isEmpty()const;
	int getLength()const;

	void addHead(Node<Type> &newNode);
	void addTail(Node<Type> &newNode);
	int addNode(Node<Type> &newNode, int n);

	int delHead();
	int delTail();
	int delNode(int n);

	int getHead(Node<Type> &node);
	int getTail(Node<Type> &node);
	int getNode(Node<Type> &node, int n);

	int modifyHead(const Type &data);
	int modifyTail(const Type &data);
	int modifyNode(const Type &data, int n);

	int show()
	{
		Node<Type> *tmp;

		if (isEmpty())
		{
			return -1;
		}

		tmp = first;

		while(tmp)
		{
			printf("%d->", tmp->data);
			tmp = tmp->next;
		}
		printf("NULL\n");
	}
};

template <class Type>
int SingleList<Type>::createNode(Node<Type> **newNode, const Type &data)
{
	*newNode = new Node<Type>(data);
	if (NULL == *newNode)
	{
		return -1;
	}

	return 0;
}

template <class Type>
int SingleList<Type>::isEmpty()const
{
	return (first == NULL);
}

template <class Type>
int SingleList<Type>::getLength()const
{
	int len;
	Node<Type> *tmp;

	len = 0;
	tmp = first;

	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}

	return len;
}

template <class Type>
void SingleList<Type>::addHead(Node<Type> &newNode)
{
	if (isEmpty())
	{
		first = &newNode;
		return;
	}

	newNode.next = first;
	first = &newNode;
}

template <class Type>
void SingleList<Type>::addTail(Node<Type> &newNode)
{
	Node<Type> *tmp;

	if (isEmpty())
	{
		first = &newNode;
		return;
	}

	tmp = first;

	while (tmp->next != NULL)
	{
		tmp = tmp->next;
	}

	tmp->next = &newNode;
}

template <class Type>
int SingleList<Type>::addNode(Node<Type> &newNode, int n)
{
	Node<Type> *tmp, *pre;

	tmp = first;

	if (1 == n)
	{
		first = &newNode;
		first->next = tmp;
		return 0;
	}

	while (--n)
	{
		if (tmp == NULL)
		{
			return -1;
		}
		pre = tmp;
		tmp = tmp->next;
	}

	newNode.next = pre->next;
	pre->next = &newNode;
}

template <class Type>
int SingleList<Type>::delHead()
{
	Node<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	tmp = first;
	first = tmp->next;

	delete(tmp);

	return 0;
}

template <class Type>
int SingleList<Type>::delTail()
{
	Node<Type> *tmp, *pre;

	if (isEmpty())
	{
		return -1;
	}

	tmp = first;
	pre = first;

	while (tmp->next)
	{
		pre = tmp;
		tmp = tmp->next;
	}

	if (tmp == first)
	{
		first = NULL;
	}

	pre->next = NULL;
	delete(tmp);

	return 0;
}

template <class Type>
int SingleList<Type>::delNode(int n)
{
	Node<Type> *tmp, *pre;

	tmp = first;
	pre = first;

	while(n--)
	{
		if (tmp == NULL)
		{
			return -1;
		}
		pre = tmp;
		tmp = tmp->next;
	}

	if (tmp == pre)
	{
		first = NULL;
	}
	pre->next = tmp->next;
	delete(tmp);

	return 0;
}

template <class Type>
int SingleList<Type>::getHead(Node<Type> &node)
{
	if (isEmpty())
	{
		return -1;
	}

	node = *first;

	return 0;
}

template <class Type>
int SingleList<Type>::getTail(Node<Type> &node)
{
	Node<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	tmp = first;

	while (tmp->next)
	{
		tmp = tmp->next;
	}

	node = *tmp;

	return 0;
}

template <class Type>
int SingleList<Type>::getNode(Node<Type> &node, int n)
{
	Node<Type> *tmp;

	tmp = first;

	while (n--)
	{
		if (tmp == NULL)
		{
			return -1;
		}
		tmp = tmp->next;
	}

	node = *tmp;

	return 0;
}

template <class Type>
int SingleList<Type>::modifyHead(const Type &data)
{
	if (isEmpty())
	{
		return -1;
	}

	first->data = data;
}

template <class Type>
int SingleList<Type>::modifyTail(const Type &data)
{
	Node<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	tmp = first;
	while (tmp->next)
	{
		tmp = tmp->next;
	}

	tmp->data = data;

	return 0;
}

template <class Type>
int SingleList<Type>::modifyNode(const Type &data, int n)
{
	Node<Type> *tmp;

	tmp = first;

	while(--n)
	{
		if (tmp == NULL)
		{
			return -1;
		}

		tmp = tmp->next;
	}

	tmp->data = data;

	return 0;
}

template <class Type>
SingleList<Type>::~SingleList()
{
	while(!isEmpty())
	{
		delHead();
	}
}

int main(int argc, char *argv[])
{
	int i;
	SingleList<int> list;
	Node<int> *node;

	for (i = 0; i < 9; i++)
	{
		list.createNode(&node, i);
		list.addTail(*node);
	}
	list.show();

	list.createNode(&node, 100);
	list.addNode(*node, 4);
	list.show();

	list.createNode(&node, 78);
	list.addHead(*node);
	list.show();

	list.delTail();
	list.show();

	list.delNode(4);
	list.show();

	list.modifyHead(1000);
	list.show();

	list.modifyTail(99);
	list.show();

	list.modifyNode(88, 2);
	list.show();

	return 0;
}
