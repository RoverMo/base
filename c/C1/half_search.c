#include <stdio.h>

int half_search(int a[], int low, int high, int num)
{
	int mid;

	while (low <= high)
	{
		mid = (low + high) >> 1;

		if (a[mid] > num)
			high = mid - 1;
		else if (a[mid] < num)
			low = mid + 1;
		else
		{
		//	mid++;
			break;
		}
	}

	return mid;
}

int main(int argc, char *argv)
{
	int a[] = {3, 4, 4, 6, 7};
	int num = 4;

	printf("%d\n", half_search(a, 0, 4, num));

	return 0;
}
