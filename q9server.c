#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {

    int server_fd, client_fd;

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char filename[100];
    char buffer[1024];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8084);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    listen(server_fd, 5);

    printf("File Server running...\n");

    while (1) {

        client_fd = accept(server_fd,
                           (struct sockaddr *)&client,
                           &len);

        recv(client_fd, filename,
             sizeof(filename), 0);

        filename[strcspn(filename, "\n")] = '\0';

        FILE *fp = fopen(filename, "r");

        char response[5000];

        if (fp == NULL) {

            sprintf(response,
                    "PID: %d\nFile does not exist.",
                    getpid());

        } else {

            sprintf(response,
                    "PID: %d\nFile contents:\n",
                    getpid());

            while (fgets(buffer, sizeof(buffer), fp)) {
                strcat(response, buffer);
            }

            fclose(fp);
        }

        send(client_fd, response,
             strlen(response) + 1, 0);

        close(client_fd);
    }

    close(server_fd);

    return 0;
}