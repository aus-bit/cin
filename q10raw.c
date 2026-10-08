#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <sys/socket.h>

int main() {

    int sock;

    char buffer[65536];

    struct sockaddr saddr;

    socklen_t saddr_size = sizeof(saddr);

    sock = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);

    if (sock < 0) {
        perror("Raw socket");
        return 1;
    }

    printf("Packet capturing started...\n");

    while (1) {

        int packet_size = recvfrom(
            sock,
            buffer,
            sizeof(buffer),
            0,
            &saddr,
            &saddr_size
        );

        if (packet_size < 0) {
            perror("recvfrom");
            break;
        }

        struct iphdr *ip =
            (struct iphdr *)buffer;

        struct sockaddr_in source, dest;

        source.sin_addr.s_addr = ip->saddr;
        dest.sin_addr.s_addr = ip->daddr;

        printf("\nPacket captured\n");

        printf("Source IP      : %s\n",
               inet_ntoa(source.sin_addr));

        printf("Destination IP : %s\n",
               inet_ntoa(dest.sin_addr));

        printf("Protocol       : %d\n",
               ip->protocol);

        printf("Packet Size    : %d bytes\n",
               packet_size);
    }

    close(sock);

    return 0;
}