#include "net.h"
#include <malloc.h>

#define MAX_SOCK_NUM  32

static struct socket *g_sock_fds[MAX_SOCK_NUM];
static struct list_node udp_port_list;
static struct list_node tcp_port_list;

static int __init__ net_init()
{
	list_head_init(&udp_port_list);
	list_head_init(&tcp_port_list);
}

int socket(int domain, int type, int protocol)
{
	int fd;
	struct socket *sock;

	for (fd = 1; fd < MAX_SOCK_NUM; fd++)
	{
		if (NULL == g_sock_fds[fd])
		{
			sock = (struct socket *)malloc(sizeof(*sock));
			if (NULL == sock)
			{
				return -ENOMEM;
			}

			sock->type		= type;
			sock->flags		= protocol;
			sock->family	= domain;
			g_sock_fds[fd]	= sock;

			return fd;
		}
	}

	return -ENODEV;
}

int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
	struct list_node *iter;
	struct port *port;
	struct list_node *list;

	switch (g_sock_fds[sockfd]->type)
	{
		case STREAM :
			list = tcp_port_list;
			break;

		case SOCK_DGRAM :
			list = udp_port_list;
			break;

		default :
			printf("Not support\n");
	}

	list_for_each(iter, list)
	{
		port = OFF2BASE(iter, struct port, next);
		if (port->port_num == ((sockaddr_in *)addr)->sin_port)
		{
			return -EBUSY;
		}
	}

	port = (struct port *)malloc(sizeof(*port));
	if (port == NULL)
	{
		return -ENOMEM;
	}
	port->port_num = ((sockaddr_in *)addr)->sin_port;
	list_head_init(&port->rx_qu);
	list_head_init(&port->tx_qu);
	list_add_tail(port, list);

	g_sock_fds[sockfd]->port_qu = port;

	return 0;
}

void udp_send_packet(struct sock_buff *skb)
{
	struct udp_header *udp_hdr;

	skb->data -= UDP_HDR_LEN;
	skb->size += UDP_HDR_LEN;

	udp_hdr = (struct udp_header *)skb->data;

	udp_hdr->src_port = skb->sock->addr.src_port;
	udp_hdr->des_port = skb->sock->addr.des_port;
	udp_hdr->udp_len  = CPU_TO_BE16(skb->size);
	udp_hdr->chksum  = 0;

	ip_send_packet(skb, PROT_UDP);
}

ssize_t sendto(int sockfd, const void *buf, size_t len, int flags, const struct sockaddr *dest_addr, socklen_t addrlen)
{
	struct socket *sock;
	struct sock_buff *skb;

	sock = g_sock_fds(fd);

	if (NULL == sock)
	{
		return -EINVAL;
	}

	skb = skb_alloc(ETH_HDR_LEN + IP_HDR_LEN + UDP_HDR_LEN, len);
	skb->sock = sock;
	memcpy(skb->data, buf, len);
	udp_send_packet(skb);

	return n;
}

struct sock_buff *udp_recv_packet(struct socket *sock)
{
	struct list_node *first;
	struct sock_buff *skb;
	u32 psr;

	while (1)
	{
		int ret;
		char key;

		ret = uart_read(CONFIG_DBGU_ID, (u8 *)&key, 1, WAIT_ASYNC);
		if (ret > 0 && key == CHAR_CTRL_C)
			return NULL;

		netif_rx_poll();

		lock_irq_psr(psr);
		if (!list_is_empty(&sock->rx_qu))
		{
			unlock_irq_psr(psr);
			break;
		}
		unlock_irq_psr(psr);

		udelay(10);
	}

	lock_irq_psr(psr);
	first = sock->port_qu->rx_qu.next;
	list_del_node(first);
	unlock_irq_psr(psr);

	skb = OFF2BASE(first, struct sock_buff, node);

	return skb;
}

ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags, struct sockaddr *src_addr, socklen_t *addrlen)
{
	struct socket *sock;
	struct sock_buff *skb;
	u32 pkt_len;

	sock = get_sock(fd);

	if (NULL == sock)
	{
		return -EINVAL;
	}

	skb = udp_recv_packet(sock);
	if(NULL == skb)
	{
		return 0;
	}

	pkt_len   = skb->size <= n ? skb->size : n;
	memcpy(buf, skb->data, pkt_len);

	skb_free(skb);

	return pkt_len;
}
