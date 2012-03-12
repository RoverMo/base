#include <stdio.h>

#define LEN(a) sizeof(a) / sizeof(a[0])

/*typedef struct node{
	int num;
}node_t;

void insert_sort(node_t a[], int len)
{
	int i;
	int j;
	node_t temp;

	for (i = 1; i < len; i++)
	{
		temp = a[i];

		for (j = i - 1; j >= 0; j--)
		{
			if (temp.num < a[j].num)
			{
				a[j + 1] = a[j];
			}
			else
			{
				break;
			}
		}
		a[j + 1] = temp;
	}
}*/

int half_search(int a[], int low, int high, int temp)
{
    int mid;

    while (low <= high)
    {
        mid = (low + high) >> 1;

        if (a[mid] > temp)
            high = mid - 1;
        else if (a[mid] < temp)
            low = mid + 1;
        else
            break;
    }

    return mid;
}

void insert_sort(int a[], int len)
{
	int i, j;
	int temp;
	int index;

	for (i = 1; i < len; i++)
	{
		temp = a[i];

		index = half_search(a, 0, i, temp);

		if (a[index] < temp)
			index++;

		for (j = i; j > index; j--)
			a[j] = a[j - 1];
		a[index] = temp;
	}
}

int main(int argc, char *argv[])
{
	int i;
	int a[] = {5, 6, 1, 3, 7, 4, 2, 2, 2};

	insert_sort(a, LEN(a));

	for(i = 0; i < LEN(a); i++)
	{
		printf("%d  ", a[i]);
	}
	printf("\n");

	return 0;
}
