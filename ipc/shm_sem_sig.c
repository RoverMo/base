#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <signal.h>

#define SIZE	256
#define SIGNUM	(SIGUNUSED + 3)

static int shm_id;
static int sem_id[2];

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short  *array;
	struct seminfo  *__buf;
};

static int sem_init(int sem_id, int res)
{
	union semun sem;

	sem.val = res;

	return semctl(sem_id, 0, SETVAL, sem);
}

static int sem_destory(int sem_id)
{
	return semctl(sem_id, 0, IPC_RMID);
}

static int sem_v(int sem_id)
{
	int ret;
	struct sembuf semb;

	semb.sem_num = 0;
	semb.sem_op	 = 1;
	semb.sem_flg = SEM_UNDO;

	ret = semop(sem_id, &semb, 1);
	if (ret < 0)
	{
		perror("sem_v failed");
	}

	return ret;
}

static int sem_p(int sem_id)
{
	int ret;
	struct sembuf semb;

	semb.sem_num = 0;
	semb.sem_op	 = -1;
	semb.sem_flg = SEM_UNDO;

	ret = semop(sem_id, &semb, 1);
	if (ret < 0)
	{
		perror("sem_p failed");
	}

	return ret;
}

static void sig_handler(int sig_num)
{
	int ret;

	sem_destory(sem_id[0]);
	sem_destory(sem_id[1]);

	ret = shmctl(shm_id, IPC_RMID, NULL);
	if (ret < 0)
	{
		perror("remove share memory failed");
	}
	else
	{
		printf("remove semaphore success!\n");
		printf("remove share memory success!\n");
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	char *buf;
	int ret;
	int num = 0;

	shm_id = shmget((key_t)8, SIZE, IPC_CREAT | IPC_EXCL);
	if (shm_id < 0)
	{
		perror("create failed");
		return shm_id;
	}

	buf = shmat(shm_id, NULL, SHM_W | SHM_R);
	if ((void *)-1 == buf)
	{
		perror("shmat failed");
		goto rm_shm;
	}

	sem_id[0] = semget((key_t)10, 1, IPC_CREAT | IPC_EXCL);
	if (sem_id[0] < 0)
	{
		perror("semget failed");
		goto rm_shm;
	}

	ret = sem_init(sem_id[0], 1);
	if (ret < 0)
	{
		perror("sem_init failed");
		goto rm_sem0;
	}

	sem_id[1] = semget((key_t)11, 1, IPC_CREAT | IPC_EXCL);
	if (sem_id[1] < 0)
	{
		perror("semget failed");
		goto rm_sem0;
	}

	ret = sem_init(sem_id[1], 0);
	if (ret < 0)
	{
		perror("sem_init failed");
		goto rm_sem1;
	}

	ret = fork();
	if (ret)
	{
		if (SIG_ERR == signal(SIGNUM, sig_handler))
		{
			perror("register signal failed");
			goto rm_sem1;
		}

		while (1)
		{
			sem_p(sem_id[0]);
			sprintf(buf, "share memory:%d\n", num);
			num++;
			// sleep(2);
			sem_v(sem_id[1]);
			// sem_v(sem_id);
			// sleep(1);
		}
	}
	else
	{
		while (1)
		{
			// sem_p(sem_id);
			sem_p(sem_id[1]);
			printf("%s", buf);
			// sleep(3);
			sem_v(sem_id[0]);
			sleep(2);
		}
	}

	return 0;

rm_sem1:
	sem_destory(sem_id[1]);

rm_sem0:
	sem_destory(sem_id[0]);

rm_shm:
	shmctl(shm_id, IPC_RMID, NULL);

	return -1;
}
