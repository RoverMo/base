/*
*功能：		筛选成绩大于等于80的学生信息
*参数：		stu：student结构体数组
*			len：stu长度
*返回值：	void
*输出：		成绩大于等于80的学生信息
*/

#include <stdio.h>

struct student
{
	int ID;
	int grade;
};

void select(struct student stu[], int len)
{
	int i = 0;
	printf("ID	grade\n");
	while (i < len)
	{
		if (stu[i].grade >= 80)
		{
			printf("%d	%d\n",stu[i].ID, stu[i].grade);
		}
		i++;
	}
}

int main(void)
{
	struct student stuary[] = {{1, 50}, {2, 60}, {3, 70}, {4, 80}, {5, 90}};
	int n = sizeof(stuary) / sizeof(stuary[0]);

	select(stuary, n);

	return 0;
}
