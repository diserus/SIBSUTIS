#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> 
#include <sys/mman.h>

int main(int argc, char* const argv[]) {
    int fd;
    char* map_address;
    
    fd = open("test_shared.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    if (fd == -1)
        fprintf(stderr, "open error\n");
    
    ftruncate(fd, 256);
    
    map_address = (char*)mmap(0, 256, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (map_address == MAP_FAILED)
        fprintf(stderr, "mmap error\n");
    
    close(fd);
    memcpy(map_address, "Take it easy!\0", sizeof("Take it easy!\0"));
    
    printf("Данные записаны. Нажмите Enter для завершения...\n");
    getc(stdin);
    
    munmap(map_address, 256);
    return 0;
}
