#include <stdio.h>

template <class Type> class Tree;
template <class Type> class Stack;
template <class Type> class Queue;

template <class Type>
class SNode
{
	friend class Stack<Type>;
private:
	Type data;
	SNode *next;

public:
	SNode() : next(NULL){}
	SNode(const Type &d) : next(NULL){data = d;}

	Type getData(){return data;}
};

template <class Type>
class Stack
{
private:
	SNode<Type> *top;

public:
	Stack() : top(NULL){}
	~Stack();

	int isEmpty(){return (top == NULL);}

	int push(const Type &data);
	int pop(Type &data);
	SNode<Type> *getTop()const{return top;}
};

template <class Type>
int Stack<Type> :: push(const Type &data)
{
	SNode<Type> *sNode = new SNode<Type>(data);
	if (sNode == NULL)
	{
		return -1;
	}

	sNode->next = top;
	top = sNode;

	return 0;
}

template <class Type>
int Stack<Type> :: pop(Type &d)
{
	SNode<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	d = top->data;

	tmp = top;
	top = top->next;

	delete(tmp);

	return 0;
}

template <class Type>
Stack<Type> :: ~Stack()
{
	SNode<Type> *tmp;

	while (!isEmpty())
	{
		tmp = top;
		top = top->next;

		delete(tmp);
	}
}

template <class Type>
class QNode
{
	friend class Queue<Type>;
private:
	Type data;
	QNode *next;

public:
	QNode() : next(NULL){}
	QNode(const Type &d) : next(NULL){data = d;}

	Type getData(){return data;}
};

template <class Type>
class Queue
{
private:
	QNode<Type> *front;
	QNode<Type> *rear;

public:
	Queue() : front(NULL), rear(NULL){}
	virtual ~Queue();

	int isEmpty()const{return (front == NULL);}

	int enter(const Type &d);
	int out(Type &d);
	QNode<Type> *getFront(){return front;}
};

template <class Type>
Queue<Type> :: ~Queue()
{
	QNode<Type> *tmp;

	while (!isEmpty())
	{
		tmp = front;
		front = front->next;
		delete(tmp);
	}
}

template <class Type>
int Queue<Type> :: enter(const Type &d)
{
	QNode<Type> *newNode = new QNode<Type>(d);
	if (newNode == NULL)
	{
		return -1;
	}

	if (isEmpty())
	{
		rear = newNode;
		front = newNode;
	}

	rear->next = newNode;
	rear = newNode;

	return 0;
}

template <class Type>
int Queue<Type> :: out(Type &d)
{
	QNode<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	d = front->data;

	tmp = front;
	front = front->next;

	if (isEmpty())
	{
		rear = NULL;
	}

	delete(tmp);

	return 0;
}

template <class Type>
class TNode
{
	friend class Tree<Type>;

private:
	Type data;
	TNode *child;
	TNode *sibling;

public:
	TNode():child(NULL), sibling(NULL){}
	TNode(Type d):child(NULL), sibling(NULL){data = d;}
};

template <class Type>
class Tree
{
private:
	TNode<Type> *root;
	void destory(TNode<Type> *root);
	void rootFirstTraversal(TNode<Type> *root)const;
	void rootLastTraversal(TNode<Type> *root)const;

public:
	Tree():root(NULL){}
	~Tree(){destory();}

	int create(const Type *str);
	void destory();
	int visit(const TNode<Type> *node)const;
	void rootFirstTraversal()const;
	void rootLastTraversal()const;
	int widthTraversal1()const;
	int depthTraversal()const;
};

template <class Type>
int Tree<Type> :: visit(const TNode<Type> *node)const
{
	if (node == NULL)
	{
		return 0;
	}

	printf("%c ", node->data);
}

template <class Type>
int Tree<Type> :: create(const Type *str)
{
	TNode<Type> *tNode;
	TNode<Type> *curRoot;
	TNode<Type> *tmp;
	SNode<TNode<Type> *> *sNode;
	Stack<TNode<Type> *> stack;

	if (*str == 0)
	{
		return 0;
	}

	tNode = new TNode<Type>(*str++);
	root = tNode;

	while (*str != 0)
	{
		switch (*str)
		{
		case '(':
			stack.push(tNode);
			break;

		case ')':
			stack.pop(tNode);
			break;

		case ',':
			break;

		default:
			tNode = new TNode<Type>(*str);
			if (tNode == NULL)
			{
				return -1;
			}

			sNode = stack.getTop();
			curRoot = sNode->getData();

			if (curRoot->child == NULL)
			{
				curRoot->child = tNode;
			}
			else
			{
				tmp = curRoot->child;
				while(tmp->sibling)
				{
					tmp = tmp->sibling;
				}
				tmp->sibling = tNode;
			}
		}

		str++;
	}
}

template <class Type>
void Tree<Type> :: destory(TNode<Type> *root)
{
	if (root != NULL)
	{
		destory(root->child);
		destory(root->sibling);
		delete(root);
	}
}

template <class Type>
void Tree<Type> :: destory()
{
	destory(root);
}

template <class Type>
void Tree<Type> :: rootFirstTraversal(TNode<Type> *root)const
{
	if (root != NULL)
	{
		visit(root);
		rootFirstTraversal(root->child);
		rootFirstTraversal(root->sibling);
	}
}

template <class Type>
void Tree<Type> :: rootFirstTraversal()const
{
	rootFirstTraversal(root);
}

template <class Type>
void Tree<Type> :: rootLastTraversal()const
{
	rootLastTraversal(root);
}

template <class Type>
void Tree<Type> :: rootLastTraversal(TNode<Type> *root)const
{
	if (root != NULL)
	{
		rootLastTraversal(root->child);
		rootLastTraversal(root->sibling);
		visit(root);
	}
}

template <class Type>
int Tree<Type> :: widthTraversal1()const
{
	int ret;
	Queue<TNode<Type> *> queue;
	TNode<Type> *tNode;

	if (root != NULL)
	{
		ret = queue.enter(root);
		if (ret < 0)
		{
			return -1;
		}
	}

	while (!queue.isEmpty())
	{
		queue.out(tNode);
		visit(tNode);
		tNode = tNode->child;

		while(tNode)
		{
			ret = queue.enter(tNode);
			if (ret < 0)
			{
				return -1;
			}
			tNode = tNode->sibling;
		}
	}

	return 0;
}

template <class Type>
int Tree<Type> :: depthTraversal()const
{
	int ret;
	TNode<Type> *tNode;
	Stack<TNode<Type> *> stack;

	if (root != NULL)
	{
		ret = stack.push(root);
		if (ret < 0)
		{
			return -1;
		}
	}

	while (!stack.isEmpty())
	{
		stack.pop(tNode);
		visit(tNode);

		tNode = tNode->child;
		while (tNode)
		{
			ret = stack.push(tNode);
			if (ret < 0)
			{
				return -1;
			}

			tNode = tNode->sibling;
		}
	}

	return 0;
}

int main(int argc, char *argv[])
{
	const char *str = "1(2(5,6),3,4(7,8,9))";
	Tree<char> tree;

	tree.create(str);

	tree.rootFirstTraversal();
	printf("\n");

	tree.rootLastTraversal();
	printf("\n");

	tree.widthTraversal1();
	printf("\n");

	tree.depthTraversal();
	printf("\n");

	return 0;
}
