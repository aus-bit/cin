#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sock;
    struct sockaddr_in server;

    int n, matrix[100][100];

    sock = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sock, (struct sockaddr *)&server, sizeof(server));

    printf("Enter N: ");
    scanf("%d", &n);

    srand(time(NULL));

    printf("\nGenerated Matrix:\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 50 + 1;
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    send(sock, &n, sizeof(n), 0);
    send(sock, matrix, sizeof(matrix), 0);

    char result[50];

    recv(sock, result, sizeof(result), 0);

    printf("\nServer says: %s\n", result);

    close(sock);

    return 0;
}