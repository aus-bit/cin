#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <windows.h>

#pragma comment(lib, "ws2_32.lib")

SOCKET sock;

DWORD WINAPI receive_messages(LPVOID arg)
{
    char message[1024];
    int bytes;

    while (1)
    {
        memset(message, 0, sizeof(message));

        bytes = recv(sock, message, sizeof(message) - 1, 0);

        if (bytes <= 0)
        {
            printf("\nServer disconnected.\n");
            break;
        }

        message[bytes] = '\0';

        printf("\nOther client: %s", message);
        printf("You: ");
        fflush(stdout);
    }

    return 0;
}

int main()
{
    WSADATA wsa;
    struct sockaddr_in server;

    char message[1024];

    /* Start Winsock */
    WSAStartup(MAKEWORD(2, 2), &wsa);

    /* Create socket */
    sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock == INVALID_SOCKET)
    {
        printf("Socket creation failed.\n");
        return 1;
    }

    /* Server details */
    server.sin_family = AF_INET;
    server.sin_port = htons(8082);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Connect to server */
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        printf("Connection failed.\n");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    printf("Connected to chat server!\n");

    /* Thread for receiving messages */
    CreateThread(
        NULL,
        0,
        receive_messages,
        NULL,
        0,
        NULL
    );

    /* Send messages */
    while (1)
    {
        printf("You: ");
        fgets(message, sizeof(message), stdin);

        if (strncmp(message, "exit", 4) == 0)
            break;

        send(sock, message, strlen(message), 0);
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}