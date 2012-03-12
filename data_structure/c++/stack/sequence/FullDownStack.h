#pragma once

#include "stack.h"

template <class Type>
class FullDownStack : public Stack<Type>
{
private:
	using Stack<Type>::top;
	using Stack<Type>::data;

public:
	FullDownStack(){top = LEN;}
	~FullDownStack(){}

	int IsEmpty()const;
	int IsFull() const;

	int Pop(Type &);
	int Push(const Type &);
};

template <class Type>
int FullDownStack<Type>::IsFull() const
{
	return (top == 0);
}

template <class Type>
int FullDownStack<Type>::IsEmpty() const
{
	return (top == LEN);
}

template <class Type>
int FullDownStack<Type>::Pop(Type &elem)
{
	if (!IsEmpty())
	{
		elem = data[top++];
		return 0;
	}

	return -1;
}

template <class Type>
int FullDownStack<Type>::Push(const Type &elem)
{
	if (!IsFull())
	{
		data[--top] = elem;
		return 0;
	}

	return -1;
}
