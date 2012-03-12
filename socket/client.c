#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define SERVER_PORT 12041
#define LEN			128

int main(int argc, char *argv[])
{
	int ret;
	int sock;
	int addr_len;
	int nbytes;
	int flag;
	char tbuf[LEN];
	struct sockaddr_in local_addr, remote_addr;

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("create socket failed");
		return -1;
	}

	flag = 0;
	local_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &local_addr.sin_addr);
	local_addr.sin_port = htons(0);

	remote_addr.sin_family = AF_INET;
	inet_aton("127.0.0.1", &remote_addr.sin_addr);
	remote_addr.sin_port = htons(SERVER_PORT);

	addr_len = sizeof(remote_addr);

	ret = bind(sock, (struct sockaddr *)&local_addr, sizeof(local_addr));
	if (ret < 0)
	{
		perror("bind failed");
		close(sock);
		return -1;
	}

	while (1)
	{
		scanf("%s", tbuf);
		if (strcmp(tbuf, "q") == 0)
		{
			break;
		}

		nbytes = sendto(sock, tbuf, strlen(tbuf) + 1, 0, (struct sockaddr *)&remote_addr, addr_len);
		if (nbytes < 0)
		{
			perror("Send data failed");
			close(sock);
			return -1;
		}

		printf("%d\n sented\n", nbytes);
	}

	close(sock);

	return 0;
}
