#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char buffer[100];
    char time_string[100];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8083);

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Time Server running...\n");

    while (1) {

        recvfrom(sock, buffer, sizeof(buffer), 0,
                 (struct sockaddr *)&client, &len);

        time_t now = time(NULL);

        strcpy(time_string, ctime(&now));

        sendto(sock, time_string, strlen(time_string) + 1, 0,
               (struct sockaddr *)&client, len);
    }

    close(sock);

    return 0;
}