#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define NUM_SENDS 5

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr = {0};
    char buffer[BUFFER_SIZE] = {0};
    int num;

    if (argc != 4)
        exit(1);

    num = atoi(argv[3]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        perror("Ошибка создания сокета");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0)
    {
        perror("Неверный IP-адрес");
        close(sockfd);
        exit(1);
    }

    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0)
    {
        perror("Ошибка подключения к серверу");
        close(sockfd);
        exit(1);
    }

    while (1)
    {
        sprintf(buffer, "%d", num);

        if (write(sockfd, buffer, strlen(buffer)) < 0)
        {
            perror("Ошибка отправки данных");
            close(sockfd);
            exit(1);
        }

        sleep(num);

        memset(buffer, 0, BUFFER_SIZE);
    }

    close(sockfd);
    return 0;
}
