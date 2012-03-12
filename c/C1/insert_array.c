#include <stdio.h>

#define LEN(a) (sizeof((a)) / sizeof((a)[0]))

void insert_array(int a[], int len, int num)
{
	int i;
	int index = 0;

	for (i = 0; i < len - 1 && a[i] < num; i++)
		index++;
	for (i = len - 1; i > index; i--)
		a[i] = a[i - 1];
	a[index] = num;
}

int main()
{
	int a[6] = {1, 2, 4, 5, 6};
	int num;
	int i;

	scanf("%d", &num);
	insert_array(a, LEN(a), num);

	for (i = 0; i < LEN(a); i++)
		printf("%d\t", a[i]);
	printf("\n");

	return 0;
}
