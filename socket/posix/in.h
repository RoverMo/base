#pragma once

#include "types.h"

#define __SOCK_SIZE__	16

struct in_addr
{
	in_addr_t s_addr;
};

struct sockaddr_in
{
	sa_family_t sin_family;
	unsigned short sin_port;
	unsigned char __pad[16 - sizeof(sin_family) - sizeof(sin_port)];
};

struct sockaddr
{
	sa_family_t sin_family;
	unsigned char sa_data[16 - sizeof(sin_family)];
};
