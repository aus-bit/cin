#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int sock;

    struct sockaddr_in server;

    char filename[100];
    char response[5000];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8084);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock,
            (struct sockaddr *)&server,
            sizeof(server));

    printf("Enter filename: ");
    fgets(filename, sizeof(filename), stdin);

    send(sock, filename,
         strlen(filename) + 1, 0);

    recv(sock, response,
         sizeof(response), 0);

    printf("\n%s\n", response);

    close(sock);

    return 0;
}