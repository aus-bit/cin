#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>

int clients[100];
int count = 0;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void broadcast(char *message, int sender) {

    pthread_mutex_lock(&lock);

    for (int i = 0; i < count; i++) {
        if (clients[i] != sender) {
            send(clients[i], message, strlen(message), 0);
        }
    }

    pthread_mutex_unlock(&lock);
}

void *handle_client(void *arg) {

    int client = *(int *)arg;
    char message[1024];

    while (1) {

        memset(message, 0, sizeof(message));

        int n = recv(client, message, sizeof(message), 0);

        if (n <= 0)
            break;

        printf("Message: %s\n", message);

        broadcast(message, client);
    }

    close(client);

    return NULL;
}

int main() {

    int server_fd;

    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8082);

    bind(server_fd, (struct sockaddr *)&server, sizeof(server));

    listen(server_fd, 10);

    printf("Chat Server running on port 8082...\n");

    while (1) {

        int client_fd = accept(server_fd,
                               (struct sockaddr *)&client,
                               &len);

        pthread_mutex_lock(&lock);

        clients[count++] = client_fd;

        pthread_mutex_unlock(&lock);

        pthread_t thread;

        pthread_create(&thread, NULL,
                       handle_client, &client_fd);

        pthread_detach(thread);
    }

    close(server_fd);

    return 0;
}