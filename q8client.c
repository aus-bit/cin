#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;

    struct sockaddr_in server;
    socklen_t len = sizeof(server);

    char message[] = "TIME";
    char time_string[100];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8083);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    sendto(sock, message, strlen(message) + 1, 0,
           (struct sockaddr *)&server, sizeof(server));

    recvfrom(sock, time_string, sizeof(time_string), 0,
             (struct sockaddr *)&server, &len);

    printf("Server Time: %s", time_string);

    close(sock);

    return 0;
}