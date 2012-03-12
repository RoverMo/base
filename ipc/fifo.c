#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 128

int main(int argc, char *argv[])
{
	int ret;
	int fd;
	int num;
	char rbuf[SIZE];
	char tbuf[SIZE];
	const char *path = "/tmp/fifo";

	ret = mkfifo(path, (mode_t)0666);
	if (ret < 0)
	{
		perror("mkfifo failed");
		return ret;
	}

	fd = open(path, O_RDWR);
	if (fd < 0)
	{
		perror("open error");
		return fd;
	}

	num = 0;

	ret = fork();
	if (ret)
	{
		while(1)
		{
			ret = sprintf(tbuf, "message %d\n", num++);
			ret = write(fd, tbuf, ret + 1);
			if (ret < 0)
			{
				perror("write failed");
				return ret;
			}
			sleep(1);
		}
	}
	else
	{
		while(1)
		{
			ret = read(fd, rbuf, SIZE);
			if (ret < 0)
			{
				perror("read failed");
				return ret;
			}
			printf("%s", rbuf);
			sleep(2);
		}
	}

	return 0;
}
