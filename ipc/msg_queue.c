#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define SIZE	128
#define SIGNUM	(SIGUNUSED + 4)

static int msg_que_id;

static void sig_handler(int sig_num)
{
	int ret;

	ret = msgctl(msg_que_id, IPC_RMID, NULL);
	if (ret < 0)
	{
		perror("remove message queue failed");
	}
	else
	{
		printf("remove message queue success!\n");
	}

	exit(1);
}

int main(int argc, char *argv[])
{
	int ret;
	char tbuf[SIZE];
	char rbuf[SIZE];
	int num;

	msg_que_id = msgget((key_t)3, IPC_CREAT | IPC_EXCL);
	if (msg_que_id < 0)
	{
		perror("msgget failed");
		return msg_que_id;
	}

	num = 0;

	ret = fork();
	if (ret)
	{
		if (SIG_ERR == signal(SIGNUM, sig_handler))
		{
			perror("register signal failed");
			msgctl(msg_que_id, IPC_RMID, NULL);
			return -1;
		}

		while (1)
		{
			ret = sprintf(tbuf, "message: %d\n", num);
			num++;

			ret = msgsnd(msg_que_id, tbuf, ret + 1, 0);
			if (ret < 0)
			{
				perror("msgsnd failed");
				msgctl(msg_que_id, IPC_RMID, NULL);
				return ret;
			}
			sleep(1);
		}
	}
	else
	{
		while(1)
		{
			ret = msgrcv(msg_que_id, rbuf, SIZE, 0, 0);
			if (ret < 0)
			{
				perror("msgrcv failed");
				msgctl(msg_que_id, IPC_RMID, NULL);
				return ret;
			}
			printf("%s", rbuf);
			sleep(2);
		}
	}

	return 0;
}
