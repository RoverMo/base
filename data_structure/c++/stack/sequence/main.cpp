#include <stdio.h>
#include "EmptyDownStack.h"

int main(int argc, char *argv[])
{
	int i;
	int elem;
	Stack<int> *stack;
	EmptyDownStack<int> edStack;

	stack = &edStack;

	for (i = 0; i < LEN; i++)
	{
		stack->Push(i);
	}

	for (i = 0; i < LEN; i++)
	{
		stack->Pop(elem);
		printf("%d ", elem);
	}
	printf("\n");

	return 0;
}
