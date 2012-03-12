#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "ldm2.h"

int main(int argc, char *argv[])
{
	int fd;
	ssize_t n;
	const char *wbuf = "Hello Rover";
	char rbuf[BUF_SIZE];
	int ret;

	fd = open("/dev/ldm2", O_RDWR);
	if (fd < 0)
	{
		perror("open()");
	}

	n = write(fd, wbuf, strlen(wbuf));
	if (n < 0)
	{
		perror("write()");
		close(fd);
		return fd;
	}
	printf("n = %ld\n", n);

	n = read(fd, rbuf, BUF_SIZE);
	if (n < 0)
	{
		perror("read()");
		close(fd);
		return fd;
	}
	printf("%s\n", rbuf);
	printf("n = %ld\n", n);

	ret = ioctl(fd, LDM2_CMD_1, rbuf);
	if (ret < 0)
	{
		close(fd);
		perror("ioctl()");
		return ret;
	}
	printf("%s\n", rbuf);

	close(fd);

	return 0;
}
