#include "../includes/ft_ping.h"

int main(int argc, char *argv[]) {

    t_params param;

    initParams(argc, argv, &param);

    // Création du socket ICMP
    if((param.sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0){
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    // Configuration de l'adresse de destination
    memset(&param.addr, 0, sizeof(param.addr));
    param.addr.sin_family = AF_INET;
    param.addr.sin_addr.s_addr = inet_addr(param.ip_addr);

    // Construction du paquet ICMP Echo Request
    memset(&param.icmp_pkt, 0, sizeof(param.icmp_pkt));
    param.icmp_pkt.icmp_type = ICMP_ECHO;
    param.icmp_pkt.icmp_code = 0;
    param.icmp_pkt.icmp_id = getpid();
    param.icmp_pkt.icmp_seq = 1;
    param.icmp_pkt.icmp_cksum = calculate_checksum(&param.icmp_pkt, sizeof(param.icmp_pkt));

    // Envoi du paquet ICMP
    if(sendto(param.sockfd, &param.icmp_pkt, sizeof(param.icmp_pkt), 0, (struct sockaddr*)&param.addr, sizeof(param.addr)) <= 0){
        perror("sendto");
        close(param.sockfd);
        exit(EXIT_FAILURE);
    }
    printf("Ping envoyé à %s\n", param.ip_addr);

    // Réception de la réponse
    if(recvfrom(param.sockfd, param.recv_buf, sizeof(param.recv_buf), 0, (struct sockaddr*)&param.recv_addr, &param.addr_len) <= 0){
        perror("recvfrom");
        close(param.sockfd);
        exit(EXIT_FAILURE);
    }

    // Vérification du type de paquet reçu
    struct ip *ip_hdr = (struct ip*)param.recv_buf;
    struct icmp *icmp_resp = (struct icmp*)(param.recv_buf + (ip_hdr->ip_hl << 2));

    if(icmp_resp->icmp_type == ICMP_ECHOREPLY){
        printf("Réponse de %s: bytes=%d time=%.2fms\n", param.ip_addr, ntohs(ip_hdr->ip_len) - (ip_hdr->ip_hl << 2),
               0.0); // Pour simplifier, le temps n'est pas mesuré ici
    } else {
        printf("Type ICMP inattendu: %d\n", icmp_resp->icmp_type);
    }

    close(param.sockfd);
    return 0;
}
