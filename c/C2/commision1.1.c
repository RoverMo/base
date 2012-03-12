#include <stdio.h>

#define LOCKPRICE	45
#define STOCKPRICE	30
#define BARRELPRICE	25
#define PRODUCELOCKS	70
#define PRODUCESTOCKS	80
#define PRODUCEBARRELS	90

int input(char *ch,int lower)
{
	int num;
	printf("%s:",ch);
	scanf("%d",&num);
	while (num < lower)
	{
		printf("It is wrong,please input again:");
		getchar();
		scanf("%d",&num);
	}
	return num;
}
int statistics(int allnum,int total,int num,char *ch)
{
	while (total > allnum)
	{
		total -= num;
		printf("Only %d %s\n",allnum-total,ch);
		getchar();
		num = input(ch,0);
		total += num;
	}
	return total;
}

int totalsales(int totalLocks,int totalStocks,int totalBarrels)
{
	return LOCKPRICE*totalLocks+STOCKPRICE*totalStocks+BARRELPRICE*totalBarrels;
}

void totalcommision(int sales)
{
	double commission;
	if(sales > 1800)
	{
		commission = 220+0.2*(sales-1800);//220=0.1*100+800*0.15
	}
	else if (sales > 1000)
	{
		commission = 100+0.15*(sales-1000);//100=0.1*1000
	}
	else
	{
		commission = 0.1*sales;
	}
	printf("Commission is $%f.\n",commission);
}

int main(int argc, char *argv[])
{
	int totalLocks		= 0;
	int totalStocks		= 0;
	int totalBarrels	= 0;
	int locks,stock,barrels;
	double sales;

	do {
		locks = input("Locks",-1);
		if (locks != -1)
		{
			totalLocks += locks;xc6
			totalLocks = statistics(PRODUCELOCKS,totalLocks,locks,"Locks");

			stock = input("Stocks",0);
			totalStocks += stock;
			totalStocks = statistics(PRODUCESTOCKS,totalStocks,stock,"Stocks");

			barrels = input("Barrels",0);
			totalBarrels += barrels;
			totalBarrels = statistics(PRODUCEBARRELS,totalBarrels,barrels,"Barrels");
		}
	} while (locks != -1);

	printf("totalLocks = %d,totalStocks = %d,totalBarrels = %d.\n",totalLocks,totalStocks,totalBarrels);
	if ((totalLocks == 0) || (totalStocks == 0) || (totalBarrels == 0))
		printf("Does not meet the requirements.\n");
	else
	{
		sales = totalsales(totalLocks,totalStocks,totalBarrels);
		totalcommision(sales);
	}

	return 0;
}
