#include <stdio.h>

int main()
{
	int i,j,num=6,tmp=6,sum=0;
	for(j=2;j<=num;j++)
	{
		for(i=2;i<=(int)sqrt(j);i++)
			if(j%i==0)
				break;
			if(i>sqrt(j)&&num%j==0)
			{
				//printf("%d ",j);
				num=num/j;
				sum=sum+j;
				i=2;
				j--;
			}
	}
	printf("%d",sum+1);
	printf("\n");
	return 0;
}
