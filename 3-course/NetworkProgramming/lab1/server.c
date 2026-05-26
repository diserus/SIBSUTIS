#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
  int sockfd;                                             
  struct sockaddr_in server_addr = {0}, client_addr = {0}; 
  socklen_t addr_len = sizeof(client_addr);
  char buffer[BUFFER_SIZE] = {0};
  int received_num = 0, transformed_num = 0;

 
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd < 0) {
    perror("Ошибка создания сокета");
    exit(1);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = INADDR_ANY; 
  server_addr.sin_port = 0;                

  if (bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Ошибка привязки сокета");
    close(sockfd);
    exit(1);
  }

  socklen_t len = sizeof(server_addr);
  if (getsockname(sockfd, (struct sockaddr *)&server_addr, &len) < 0) {
    perror("Ошибка получения информации о сокете");
    close(sockfd);
    exit(1);
  }

  printf("Сервер запущен на порту: %d\n", ntohs(server_addr.sin_port));

  while (1) {

    memset(buffer, 0, BUFFER_SIZE);
    int recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                            (struct sockaddr *)&client_addr, &addr_len);

    if (recv_len < 0) {
      perror("Ошибка получения данных");
      continue;
    }

    received_num = atoi(buffer);

    printf("Получено от клиента %s:%d -> %d\n", inet_ntoa(client_addr.sin_addr),
           ntohs(client_addr.sin_port), received_num);

    transformed_num = received_num * received_num;

    memset(buffer, 0, BUFFER_SIZE);
    sprintf(buffer, "%d", transformed_num);
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr,
           addr_len);

    printf("Отправлено клиенту: %d\n\n", transformed_num);
  }

  close(sockfd);
  return 0;
}
