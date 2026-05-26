#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_CLIENTS 10

typedef struct
{
    int fd;
    struct sockaddr_in addr;
} client_t;

int main()
{
    int server_fd;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    int max_fd, activity;
    fd_set read_fds;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        perror("Ошибка создания сокета");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = 0;

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0)
    {
        perror("Ошибка привязки сокета");
        close(server_fd);
        exit(1);
    }

    socklen_t len = sizeof(server_addr);
    if (getsockname(server_fd, (struct sockaddr *)&server_addr, &len) < 0)
    {
        perror("Ошибка получения информации о сокете");
        close(server_fd);
        exit(1);
    }

    printf("Сервер запущен на порту: %d\n", ntohs(server_addr.sin_port));

    if (listen(server_fd, MAX_CLIENTS) < 0)
    {
        perror("Ошибка при listen");
        close(server_fd);
        exit(1);
    }

    client_t clients[MAX_CLIENTS] = {0};
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        clients[i].fd = -1;
    }

    while (1)
    {
        FD_ZERO(&read_fds);
        FD_SET(server_fd, &read_fds);
        max_fd = server_fd;

        for (int i = 0; i < MAX_CLIENTS; i++)
        {
            if (clients[i].fd > 0)
            {
                FD_SET(clients[i].fd, &read_fds);
                if (clients[i].fd > max_fd)
                {
                    max_fd = clients[i].fd;
                }
            }
        }

        activity = select(max_fd + 1, &read_fds, NULL, NULL, NULL);
        if (activity < 0)
        {
            perror("Ошибка select");
            continue;
        }

        if (FD_ISSET(server_fd, &read_fds))
        {
            int new_fd =
                accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

            int added = 0;
            for (int i = 0; i < MAX_CLIENTS; i++)
            {
                if (clients[i].fd < 0)
                {
                    clients[i].fd = new_fd;
                    clients[i].addr = client_addr;
                    added = 1;
                    break;
                }
            }

            if (!added)
            {
                printf("Максимум клиентов достигнут\n");
                close(new_fd);
            }
        }

        for (int i = 0; i < MAX_CLIENTS; i++)
        {

            if (clients[i].fd > 0 && FD_ISSET(clients[i].fd, &read_fds))
            {
                int bytes_read = read(clients[i].fd, buffer, BUFFER_SIZE - 1);

                if (bytes_read <= 0)
                {
                    close(clients[i].fd);
                    clients[i].fd = -1;
                }
                else
                {
                    buffer[bytes_read] = '\0';
                    int received_num = atoi(buffer);

                    printf("%s:%d -> %d\n", inet_ntoa(clients[i].addr.sin_addr),
                           ntohs(clients[i].addr.sin_port), received_num);
                }
            }
        }
    }

    close(server_fd);
    return 0;
}
