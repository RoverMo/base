#pragma once

struct port
{
	unsigned long port_num;
	struct list_node rx_qu;
	struct list_node tx_qu;
	struct list_node next;
};

struct socket
{
	sa_family_t family;
	short type;
	struct port *port_qu;
	int flags;
};

enum sock_type
{
	STREAM		= 1,
	SOCK_DGRAM	= 2,
	SOCK_RAW	= 3,
	SOCK_RDM	= 4,
	SEQPACKET	= 5,
	SOCK_DCCP	= 6,
	SOCK_PACKET	= 10,
};
