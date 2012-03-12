#pragma once

#include "stack.h"

template <class Type>
class FullAscendStack : public Stack<Type>
{
private:
	using Stack<Type>::top;
	using Stack<Type>::data;

public:
	FullAscendStack(){top = -1;}
	~FullAscendStack(){}

	int IsEmpty()const;
	int IsFull() const;

	int Pop(Type &);
	int Push(const Type &);
};

template <class Type>
int FullAscendStack<Type>::IsEmpty() const
{
	return (top == -1);
}

template <class Type>
int FullAscendStack<Type>::IsFull() const
{
	return (top == (LEN - 1));
}

template <class Type>
int FullAscendStack<Type>::Pop(Type &elem)
{
	if (!IsEmpty())
	{
		elem = data[top--];
		return 0;
	}

	return -1;
}

template <class Type>
int FullAscendStack<Type>::Push(const Type &elem)
{
	if (!IsFull())
	{
		data[++top] = elem;
		return 0;
	}

	return -1;
}
