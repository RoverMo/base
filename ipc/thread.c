#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

pthread_t	thread1, thread2;
sem_t		sem1, sem2;

void *show1(void *p)
{
	int i;

	sem_wait(&sem1);
	for (i = 0; i < 5; i++)
	{
		printf("%s():%d\n", __FUNCTION__, __LINE__);
	}
	sem_post(&sem2);

	return NULL;
}

void *show2(void *p)
{
	int i;

	sem_wait(&sem2);
	for (i = 0; i < 9; i++)
	{
		printf("%s():%d\n", __FUNCTION__, __LINE__);
	}
	sem_post(&sem1);

	return NULL;
}

int main(int argc, char *argv[])
{
	int ret;

	sem_init(&sem1, 0, 1);
	sem_init(&sem2, 0, 0);

	ret = pthread_create(&thread1, NULL, show1, NULL);
	if (ret)
	{
		perror("pthread_create failed");
		return -1;
	}

	ret = pthread_create(&thread2, NULL, show2, NULL);
	if (ret)
	{
		perror("pthread_create failed");
		return -1;
	}

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);

	return 0;
}
