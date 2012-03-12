#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>

#define SERVER_PORT 12041
#define LEN			128

int main(int argc, char *argv[])
{
	int ret;
	int sock;
	int addr_len;
	char buf[LEN];
	struct sockaddr_in local_addr, remote_addr;
	int nbytes;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("Create socket failed");
		return -1;
	}

	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	local_addr.sin_port = htons(SERVER_PORT);

	remote_addr.sin_family = AF_INET;

	addr_len = sizeof(local_addr);

	ret = bind(sock, (struct sockaddr*)&local_addr, sizeof(local_addr));
	if (ret < 0)
	{
		perror("Bind failed");
		close(sock);
		return -1;
	}

	while(1)
	{
		memset(buf, 0, LEN);

		nbytes = recvfrom(sock, buf, LEN, 0, (struct sockaddr*)&remote_addr, (socklen_t *)&addr_len);

		if (nbytes < 0)
		{
			perror("Recvive data failed");
			close(sock);
			return -1;
		}

		printf("%s\n", buf);
	}
	return 0;
}
