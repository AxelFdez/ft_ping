#ifndef FT_PING_H
# define FT_PING_H

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip_icmp.h>
#include <arpa/inet.h>
#include <time.h>
#include <signal.h>

typedef struct s_params
{
	const char			*ip_addr;
	int					sockfd;
	struct sockaddr_in	addr;
	struct icmp			icmp_pkt;
	char				recv_buf[1024];
	struct sockaddr_in	recv_addr;
	socklen_t			addr_len;
	int					ttl_val;

}			t_params;

char	**ft_split(char const *s, char c);
unsigned short calculate_checksum(void *b, int len);
void initParams(int argc, char **argv, struct s_params *param);

#endif