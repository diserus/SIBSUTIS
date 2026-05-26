#include <arpa/inet.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 5

void sigchld_handler(int sig)
{
    (void)sig;

    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

void handle_client(int client_fd, struct sockaddr_in client_addr)
{
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;

    printf("[PID %d] Подключен клиент %s:%d\n", getpid(),
           inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        int received_num = atoi(buffer);

        printf("[PID %d] Получено от клиента %s:%d -> число: %d\n", getpid(),
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port),
               received_num);

        memset(buffer, 0, BUFFER_SIZE);
    }

    if (bytes_read == 0)
    {
        printf("[PID %d] Клиент %s:%d отключился\n", getpid(),
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
    }
    else
    {
        perror("Ошибка чтения данных");
    }

    close(client_fd);
    exit(0);
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);
    pid_t pid;

    signal(SIGCHLD, sigchld_handler);

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

    if (listen(server_fd, MAX_CONNECTIONS) < 0)
    {
        perror("Ошибка при переводе сокета в режим прослушивания");
        close(server_fd);
        exit(1);
    }

    printf("Ожидание подключений...\n\n");

    while (1)
    {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);

        if (client_fd < 0)
        {
            perror("Ошибка при принятии соединения");
            continue;
        }

        pid = fork();

        if (pid < 0)
        {
            perror("Ошибка создания процесса");
            close(client_fd);
            continue;
        }

        if (pid == 0)
        {
            // Дочерний процесс
            close(server_fd);
            handle_client(client_fd, client_addr);
        }
        else
        {
            // Родительский процесс
            close(client_fd);
            printf("[Родительский процесс] Создан дочерний процесс PID: %d\n\n", pid);
        }
    }

    close(server_fd);
    return 0;
}
