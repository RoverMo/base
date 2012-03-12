/*
 *用栈实现字符串反转。要求单词不要反转。
 */

#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct node
{
	char string[10];
	struct node *link;
};

struct link_stack
{
	struct node *top;
};

void init_link_stack(struct link_stack *stack)
{
	stack->top = NULL;
}

int is_empty(struct link_stack *stack)
{
	return stack->top == NULL;
}

int push(struct link_stack *stack, const char *str)
{
	struct node *newnode;

	newnode = (struct node *)malloc(sizeof(newnode));
	if (newnode == NULL)
	{
		return -1;
	}

	strcpy(newnode->string, str);
	if (is_empty(stack))
	{
		stack->top = newnode;
	}
	else
	{
		newnode->link = stack->top;
		stack->top = newnode;
	}

	return 0;
}

int pop(struct link_stack *stack, char *str)
{
	struct node *temp;

	if (is_empty(stack))
	{
		return -1;
	}

	strcpy(str, stack->top->string);

	temp = stack->top;
	stack->top = temp->link;
	free(temp);

	if (is_empty(stack))
	{
		stack->top = NULL;
	}

	return 0;
}

int main(int argc, char *argv[])
{
	int i;
	const char *p;
	const char *str = "I am Rover";
	struct link_stack stack;
	char temp[10];

	init_link_stack(&stack);

	p = str;

	while (*p)
	{
		i = 0;
		while (*p != ' ' && *p)
		{
			temp[i++] = *p++;
		}
		temp[i] = '\0';
		push(&stack, temp);
		p++;
	}

	while (!is_empty(&stack))
	{
		pop(&stack, temp);
		printf("%s\n", temp);
	}

	return 0;
}
