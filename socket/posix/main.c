#include <stdio.h>
#include "in.h"

int main(int argc, char *argv[])
{
	struct in_addr addr;

#if 0
	printf("%x\n", htonl(0x01020304));
	printf("%x\n", ntohl(htonl(0x01020304)));
	printf("%x\n", htons(0x1234));
	printf("%x\n", ntohs(htons(0x1234)));
#endif

	inet_aton("1.2.10.0x10", &addr);
	printf("%x\n", addr.s_addr);

	return 0;
}
