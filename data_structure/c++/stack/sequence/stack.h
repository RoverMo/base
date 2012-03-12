#pragma once

#define LEN 20

template <class Type>
class Stack
{
protected:
	int top;
	Type data[LEN];
public:
	Stack(){}
	virtual ~Stack(){}

	virtual int Pop(Type &elem) = 0;
	virtual int Push(const Type &elem) = 0;

	virtual int IsEmpty() const = 0;
	virtual int IsFull() const = 0;
};
