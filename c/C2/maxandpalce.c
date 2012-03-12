#include <stdio.h>

void maxaryplace(int a[], int n)
{
	int maxary = a[0];
	int maxplace = 0;
	int i = 0;
	while(n > 1)
	{
		if(a[i + 1] > a[i])
		{
			maxplace = i + 1;
			maxary = a[i + 1];
		}
		i++;
		n--;
	}
	printf("%d %d",maxplace,maxary);
} 

int main()
{
	int a[] = {1,6,1,6,4,3,26,4};
	maxaryplace(a,sizeof(a)/sizeof(a[0]));
	return 0;
}