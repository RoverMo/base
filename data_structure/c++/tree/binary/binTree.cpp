#include <stdio.h>

#define LEN 40

template <class Type> class Stack;
template <class Type> class Queue;
template <class Type> class BinTree;

template <class Type>
class SNode
{
	friend class Stack<Type>;
private:
	Type data;
	SNode *next;

public:
	SNode():next(NULL){}
	SNode(const Type &d):next(NULL){data = d;}

	Type getData(){return data;}
};

template <class Type>
class Stack
{
private:
	SNode<Type> *top;

public:
	Stack():top(NULL){}
	virtual ~Stack(){} //fixme

	int isEmpty(){return (top == NULL);}

	int createNode(SNode<Type> **node, const Type &d);

	void push(SNode<Type> &node);
	int pop();
	SNode<Type> *getTop(){return top;}
};

template <class Type>
int Stack<Type>::createNode(SNode<Type> **node, const Type &d)
{
	*node = new SNode<Type>(d);
	if (*node == NULL)
	{
		return -1;
	}

	return 0;
}

template <class Type>
void Stack<Type>::push(SNode<Type> &node)
{
	if (isEmpty())
	{
		top = &node;
	}

	node.next = top;
	top = &node;
}

template <class Type>
int Stack<Type>::pop()
{
	SNode<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

	tmp = top;
	top = top->next;

	delete(tmp);

	return 0;
}

template <class Type>
class QNode
{
	friend class Queue<Type>;
private:
	Type data;
	QNode *next;

public:
	QNode():next(NULL){}
	QNode(const Type &d):next(NULL){data = d;}

	Type getData(){return data;}
};

template <class Type>
class Queue
{
private:
	QNode<Type> *front;
	QNode<Type> *rear;

public:
	Queue():front(NULL), rear(NULL){}
	virtual ~Queue();

	int isEmpty()const{return (front == NULL);}

	int createNode(QNode<Type> **node, const Type &d);
	void enter(QNode<Type> &node);
	int out();
	QNode<Type> *getFront(){return front;}
};

template <class Type>
Queue<Type>::~Queue()
{
	while (!isEmpty())
	{
		out();
	}
}

template <class Type>
int Queue<Type>::createNode(QNode<Type> **node, const Type &d)
{
	(*node) = new QNode<Type>(d);

	if (*node == NULL)
	{
		return -1;
	}

	return 0;
}

template <class Type>
void Queue<Type>::enter(QNode<Type> &node)
{
	if (isEmpty())
	{
		front = &node;
		rear = &node;
		return;
	}

	rear->next = &node;
	rear = &node;
}

template <class Type>
int Queue<Type>::out()
{
	QNode<Type> *tmp;

	if (isEmpty())
	{
		return -1;
	}

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
	friend class BinTree<Type>;
private:
	Type data;
	TNode *lChild;
	TNode *rChild;

public:
	TNode(){}
	TNode(Type d):lChild(NULL), rChild(NULL){data = d;}

	Type getData(){return data;}
};

template <class Type>
class BinTree
{
private:
	TNode<Type> *root;
	void preTraversal(const TNode<Type> *root)const;
	void midTraversal(const TNode<Type> *root)const;
	void postTraversal(const TNode<Type> *root)const;
	void destory(TNode<Type> *root);

public:
	BinTree():root(NULL){}
	~BinTree(){destory(root);}

	void create(const Type *str);
	void destory();
	void preTraversal()const;
	void midTraversal()const;
	void postTraversal()const;
	void levelTranersal()const;
};

template <class Type>
void BinTree<Type>::create(const Type *str)
{
	int flag;
	TNode<Type> *tmp;
	TNode<Type> *curRoot;
	SNode<TNode<Type> *> *sNode;
	Stack<TNode<Type> *> stack;

	if (*str == '\0')
	{
		return;
	}

	tmp = new TNode<Type>(*str++);
	root = tmp;

	while (*str != '\0')
	{
		switch (*str)
		{
		case '(':
			flag = 0;
			stack.createNode(&sNode, tmp);
			stack.push(*sNode);
			break;

		case ')':
			stack.pop();
			break;

		case ',':
			flag = 1;
			break;

		default:
			tmp = new TNode<Type>(*str);
			sNode = stack.getTop();
			curRoot = sNode->getData();

			if (flag)
			{
				curRoot->lChild = tmp;
			}
			else
			{
				curRoot->rChild = tmp;
			}
		}

		str++;
	}
}

template <class Type>
void BinTree<Type>::destory(TNode<Type> *root)
{
	if (root != NULL)
	{
		destory(root->lChild);
		destory(root->rChild);
		delete(root);
	}
}

template <class Type>
void BinTree<Type>::destory()
{
	destory(root);
}

template <class Type>
void BinTree<Type>::preTraversal(const TNode<Type> *root)const
{
	if (root != NULL)
	{
		printf("%c ", root->data);
		preTraversal(root->lChild);
		preTraversal(root->rChild);
	}
}

template <class Type>
void BinTree<Type>::preTraversal()const
{
	preTraversal(root);
}

template <class Type>
void BinTree<Type>::midTraversal(const TNode<Type> *root)const
{
	if (root != NULL)
	{
		midTraversal(root->lChild);
		printf("%c ", root->data);
		midTraversal(root->rChild);
	}
}

template <class Type>
void BinTree<Type>::midTraversal()const
{
	midTraversal(root);
}

template <class Type>
void BinTree<Type>::postTraversal(const TNode<Type> *root)const
{
	if (root != NULL)
	{
		postTraversal(root->lChild);
		postTraversal(root->rChild);
		printf("%c ", root->data);
	}
}

template <class Type>
void BinTree<Type>::postTraversal()const
{
	postTraversal(root);
}

template <class Type>
void BinTree<Type>::levelTranersal()const
{
	Queue<TNode<Type> > queue;
	TNode<Type> tmp;
	QNode<TNode<Type> > *qNode;

	tmp = *root;

	if (root != NULL)
	{
		queue.createNode(&qNode, tmp);
		queue.enter(*qNode);
	}

	while (!queue.isEmpty())
	{
		qNode = queue.getFront();
		tmp = qNode->getData();
		printf("%c ", tmp.data);
		queue.out();

		if (tmp.lChild != NULL)
		{
			queue.createNode(&qNode, *(tmp.lChild));
			queue.enter(*qNode);
		}

		if (tmp.rChild != NULL)
		{
			queue.createNode(&qNode, *(tmp.rChild));
			queue.enter(*qNode);
		}
	}
}

int main(int argc, char *argv[])
{
	const char *str = "1(2(3,4(,5)),6(7,8))";

	BinTree<char> tree;

	tree.create(str);

	tree.preTraversal();
	printf("\n");

	tree.midTraversal();
	printf("\n");

	tree.postTraversal();
	printf("\n");

	tree.levelTranersal();
	printf("\n");

	return 0;
}
