#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUF_SIZE 32

int main(int argc, char *argv[])
{
	int fd;
	ssize_t n;
	char ch;
	const char *wbuf = "Hello Rover";
	char rbuf[BUF_SIZE];

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

	n = read(fd, rbuf, BUF_SIZE);
	if (n < 0)
	{
		perror("read()");
		close(fd);
		return fd;
	}
	printf("%s\n", rbuf);

	ioctl(fd, 100);

	// printf("ch = %x", ch);

	close(fd);

	return 0;
}
