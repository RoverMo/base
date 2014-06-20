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
	int fd;
	int ret;

	if (argc != 2)
	{
		printf("Usage: %s <cdrom_device>\n", argv[0]);
		return -EINVAL;
	}

	fd = open(argv[1], O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		printf("Can not open %s(%d)\n", argv[1], fd);
		return fd;
	}

	ret = ioctl(fd, CDROMEJECT);
	if (ret < 0)
		printf("Can not eject %s\n", argv[1]);

	close(fd);

	return 0;
}
