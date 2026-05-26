#include <arpa/inet.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define MAX_CONNECTIONS 5
#define LOG_FILE "server_log.txt"

pthread_mutex_t file_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    int client_fd;
    struct sockaddr_in client_addr;
} client_data_t;

void write_to_file(const char *client_ip, int client_port, int number)
{
    pthread_mutex_lock(&file_mutex);

    FILE *file = fopen(LOG_FILE, "a");

    if (file != NULL)
    {
        fprintf(file, "Клиент %s:%d -> число: %d\n", client_ip, client_port,
                number);
        fclose(file);
    }

    pthread_mutex_unlock(&file_mutex);
}

void *handle_client(void *arg)
{
    client_data_t *data = (client_data_t *)arg;
    int client_fd = data->client_fd;
    struct sockaddr_in client_addr = data->client_addr;

    char *client_ip = inet_ntoa(client_addr.sin_addr);
    int client_port = ntohs(client_addr.sin_port);

    char buffer[BUFFER_SIZE] = {0};
    int bytes_read = 0;

    while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1)) > 0)
    {
        buffer[bytes_read] = '\0';
        int received_num = atoi(buffer);

        write_to_file(client_ip, client_port, received_num);
        printf("%s:%d -> %d\n", client_ip, client_port, received_num);

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(client_fd);
    free(data);
    return NULL;
}

int main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr = {0}, client_addr = {0};
    socklen_t addr_len = sizeof(client_addr);
    pthread_t thread_id;

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
        perror("Ошибка при listen");
        close(server_fd);
        exit(1);
    }

    while (1)
    {
        client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len);
        if (client_fd < 0)
        {
            perror("Ошибка при accept");
            continue;
        }

        client_data_t *data = malloc(sizeof(client_data_t));
        if (data == NULL)
        {
            perror("Ошибка выделения памяти");
            close(client_fd);
            continue;
        }

        data->client_fd = client_fd;
        data->client_addr = client_addr;

        if (pthread_create(&thread_id, NULL, handle_client, data) != 0)
        {
            perror("Ошибка создания потока");
            close(client_fd);
            free(data);
            continue;
        }

        pthread_detach(thread_id);
    }

    close(server_fd);
    pthread_mutex_destroy(&file_mutex);
    return 0;
}
