/*#include <stdio.h>

void printString(void)
{
	printf("hdvkdjdlkvj\n");
}

void printfigure(int figure)
{
	printf("%d\n", figure);
}

int main(void)
{
	void (*fpstr)(void);
	void (*fpn)(int);
	fpstr = printString;
	(*fpstr)();
	fpn = printfigure;
	(*fpn)(45);
	return 0;
}*/

#include <stdio.h>

float *find(float(*pionter)[4],int n);

int main(void)
{
	static float score[][4]={{60,70,80,90},{56,89,34,45},{34,23,56,45}};
	float *p;
	int i,m;
	printf("Enter the number to be found:");
	scanf("%d",&m);
	printf("the score of NO.%d are:\n",m);
	p=find(score,m-1);
	for(i=0;i<4;i++)
		printf("%5.2f\t",*(p+i));
	return 0;
}

float *find(float(*pionter)[4],int n)/*定义指针函数*/
{
	float *pt; 
	pt=*(pionter+n);
	return (pt);
} 
