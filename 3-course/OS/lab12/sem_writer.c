#include <semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

int main() {
    int n = 0, counter = 0, fd;
    char* sh;
    sem_t *sem;
    
    fd = shm_open("/common_region", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP);
    ftruncate(fd, 6);
    sh = (char*)mmap(0, 6, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    memset(sh, 0, 6);
    
    sem = sem_open("/common_sem", 0); 
    
    while (n++ < 200) {
        sem_wait(sem);
        if (counter % 2) {
            strcpy(sh, "Hello");
        } else {
            strcpy(sh, "Bye_u");
        }
        sem_post(sem);
        counter++;
        usleep(100000); 
    }
    
    munmap(sh, 6);
    return 0;
}
