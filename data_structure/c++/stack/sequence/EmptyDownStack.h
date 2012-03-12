#pragma once

#include "stack.h"

template <class Type>
class EmptyDownStack : public Stack<Type>
{
private:
	using Stack<Type>::top;
	using Stack<Type>::data;

public:
	EmptyDownStack(){top = LEN - 1;}
	~EmptyDownStack(){}

	int IsEmpty()const;
	int IsFull() const;

	int Pop(Type &);
	int Push(const Type &);
};

template <class Type>
int EmptyDownStack<Type>::IsFull() const
{
	return (top == -1);
}

template <class Type>
int EmptyDownStack<Type>::IsEmpty() const
{
	return (top == LEN - 1);
}

template <class Type>
int EmptyDownStack<Type>::Pop(Type &elem)
{
	if (!IsEmpty())
	{
		elem = data[++top];
		return 0;
	}

	return -1;
}

template <class Type>
int EmptyDownStack<Type>::Push(const Type &elem)
{
	if (!IsFull())
	{
		data[top--] = elem;
		return 0;
	}

	return -1;
}
