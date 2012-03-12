#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define SIZE 128

int main(int argc, char *argv[])
{
	int ret;
	int pipefd[2];
	char tbuf[SIZE];
	char rbuf[SIZE];

	ret = pipe(pipefd);
	if (ret < 0)
	{
		perror("pipe failed");
		return ret;
	}

	ret = fork();
	if (ret > 0)
	{
		memset(tbuf, 0, SIZE);
		scanf("%s", tbuf);
		write(pipefd[1], tbuf, strlen(tbuf));
	}
	else
	{
		while (1)
		{
			read(pipefd[0], rbuf, SIZE);
			printf("%s\n", rbuf);
		}
	}

	close(pipefd[0]);
	close(pipefd[1]);

	return 0;
}
