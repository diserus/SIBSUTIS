#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
#define NUM_SENDS 10

int main(int argc, char *argv[])
{
    int sockfd;
    struct sockaddr_in server_addr = {0};
    socklen_t addr_len = sizeof(server_addr);
    char buffer[BUFFER_SIZE] = {0};

    if (argc != 4)
    {
        exit(1);
    }

    int num = atoi(argv[3]);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
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

    for (int i = 0; i < NUM_SENDS; i++)
    {
        sprintf(buffer, "%d", num);

        if (sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr *)&server_addr, addr_len) < 0)
        {

            perror("Ошибка отправки данных");
            close(sockfd);
            exit(1);
        }

        printf("Отправлено: %d -> \n", num);

        int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                (struct sockaddr *)&server_addr, &addr_len);

        if (recv_len < 0)
        {
            perror("Ошибка получения данных\n");
        }
        else
        {
            printf("  Получено: %s <-\n\n", buffer);
        }

        if (i < NUM_SENDS - 1)
        {
            sleep(num);
        }
    }

    close(sockfd);
    return 0;
}
