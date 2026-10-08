#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

void replace(char *str, const char *old, const char *new) {
    char buffer[2000];

    while (strstr(str, old) != NULL) {
        char *pos = strstr(str, old);

        int index = pos - str;

        buffer[0] = '\0';

        strncat(buffer, str, index);
        strcat(buffer, new);
        strcat(buffer, pos + strlen(old));

        strcpy(str, buffer);
    }
}

int main() {

    int sock;
    struct sockaddr_in server, client;
    socklen_t len = sizeof(client);

    char message[2000];

    sock = socket(AF_INET, SOCK_DGRAM, 0);

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8081);

    bind(sock, (struct sockaddr *)&server, sizeof(server));

    printf("UDP Server waiting...\n");

    recvfrom(sock, message, sizeof(message), 0,
             (struct sockaddr *)&client, &len);

    printf("Received: %s\n", message);

    replace(message, "tbh", "to be honest");
    replace(message, "ig", "I guess");
    replace(message, "tbf", "to be fair");
    replace(message, "atm", "at the moment");
    replace(message, "irl", "in real life");
    replace(message, "lol", "laughing out loud");
    replace(message, "asap", "as soon as possible");
    replace(message, "omg", "oh my god");
    replace(message, "ttyl", "talk to you later");
    replace(message, "idk", "I don't know");
    replace(message, "nvm", "never mind");

    sendto(sock, message, strlen(message) + 1, 0,
           (struct sockaddr *)&client, len);

    close(sock);

    return 0;
}