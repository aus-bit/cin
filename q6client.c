#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    char message[2000];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8081);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    printf("Enter sentence:\n");

    fgets(message, sizeof(message), stdin);

    sendto(sock, message, strlen(message) + 1, 0,
           (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock, message, sizeof(message), 0,
             (struct sockaddr *)&server, &len);

    printf("\nFormal English:\n%s\n", message);

    close(sock);

    return 0;
}