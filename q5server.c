#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server, client;
    socklen_t addrlen = sizeof(client);

    int n, matrix[100][100];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));
    listen(server_fd, 5);

    printf("Server waiting...\n");

    client_fd = accept(server_fd, (struct sockaddr *)&client, &addrlen);

    recv(client_fd, &n, sizeof(n), 0);
    recv(client_fd, matrix, sizeof(matrix), 0);

    int upper = 1, lower = 1, diagonal = 1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {

            if (i > j && matrix[i][j] != 0)
                upper = 0;

            if (i < j && matrix[i][j] != 0)
                lower = 0;

            if (i != j && matrix[i][j] != 0)
                diagonal = 0;
        }
    }

    char result[50];

    if (diagonal)
        strcpy(result, "Diagonal Matrix");
    else if (upper)
        strcpy(result, "Upper Triangular Matrix");
    else if (lower)
        strcpy(result, "Lower Triangular Matrix");
    else
        strcpy(result, "None");

    send(client_fd, result, sizeof(result), 0);

    close(client_fd);
    close(server_fd);

    return 0;
}