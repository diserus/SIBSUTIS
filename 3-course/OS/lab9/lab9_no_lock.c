#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sh = 0;

void* my_thread0() {
    int i = 0;
    for (; i < 100; i++) {
        sh++;  
    }
    return NULL;
}

void* my_thread1() {
    int i = 0;
    for (; i < 100; i++) {
        sh += 2;  
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];

    pthread_create(&th_id[0], NULL, &my_thread0, NULL);
    pthread_create(&th_id[1], NULL, &my_thread1, NULL);

    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);

    printf("%i\n", sh);

    return 0;
}
