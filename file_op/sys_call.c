#include <stdio.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/stat.h>

int main()
{
	int fd;

	fd = open("/dev/sda6", O_RDONLY);
	if (fd < 0)
	{
		perror("open failed");
	}

	return 0;
}
