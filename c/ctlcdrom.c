/*
 * 弹出光驱
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/cdrom.h>
#include <linux/errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	long fd;

	if (argc < 2)
	{
		return -EINVAL;
	}

	fd = open(argv[1], O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		return fd;
	}

	ioctl(fd, CDROMEJECT);

	close(fd);

	return 0;
}
