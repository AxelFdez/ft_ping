#include "../includes/ft_ping.h"

// Calcul du checksum ICMP
unsigned short calculate_checksum(void *b, int len) {
    unsigned short *buf = b;
    unsigned int sum=0;
    unsigned short result;

    for(sum = 0; len > 1; len -= 2)
        sum += *buf++;
    if(len == 1)
        sum += *(unsigned char*)buf;
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    result = ~sum;
    return result;
}

void handleOption(char *option, char *paramOption, int *argc, t_params *param) {
	if (strcmp(option, "-t") == 0) {
		int value = atoi(paramOption);
		if (value < 1 || value > 255) {
			printf("ping: invalid argument: %d: out of range: 1 <= value <= 255\n", value);
			exit(EXIT_FAILURE);
		}
		else if (value == 0) {
			printf("ping: invalid argument: %s", paramOption);
			exit(EXIT_FAILURE);
		}
		param->ttl_val = value;
		*argc = *argc++;
	} else if (strcmp(option, "-h") == 0) {
		printf("Usage\n  ping [options] <destination>\n");
		exit(EXIT_SUCCESS);
	} else {
		printf("Option non reconnue: %s\n", option);
		exit(EXIT_FAILURE);
	}
}

void initParams(int argc, char *argv[], t_params *param) {
	if(argc == 1){
		printf("ping: usage error: Destination address required\n");
		exit(EXIT_FAILURE);
	}
	argv = argv + 1;

	int i = 0;
	while (i < argc - 1) {
		if (argv[i][0] == '-') {
			handleOption(argv[i], argv[i + 1], &argc, param);
		}
		i++;
	}

	param->ip_addr = argv[i];

	if (param->ttl_val == 0) {
		param->ttl_val = 64;
	}

	// const char *ip_addr = argv[1];
    param->addr_len = sizeof(param->recv_addr);
    // int ttl_val = 64;


	// printf("args[0]: %s\n", args[0]);


	// param->ip_addr = argv[1];
	// param->ttl_val = 64;
}
