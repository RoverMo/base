#pragma once

#include "stack.h"

template <class Type>
class EmptyAscendStack : public Stack<Type>
{
private:
	using Stack<Type>::top;
	using Stack<Type>::data;

public:
	EmptyAscendStack(){top = 0;}
	~EmptyAscendStack(){}

	int IsEmpty()const;
	int IsFull() const;

	int Pop(Type &);
	int Push(const Type &);
};

template <class Type>
int EmptyAscendStack<Type>::IsEmpty() const
{
	return (top == 0);
}

template <class Type>
int EmptyAscendStack<Type>::IsFull() const
{
	return (top == LEN);
}

template <class Type>
int EmptyAscendStack<Type>::Pop(Type &elem)
{
	if (!IsEmpty())
	{
		top--;
		elem = data[top];
		return 0;
	}

	return -1;
}

template <class Type>
int EmptyAscendStack<Type>::Push(const Type &elem)
{
	if (!IsFull())
	{
		data[top++] = elem;
		return 0;
	}

	return -1;
}
