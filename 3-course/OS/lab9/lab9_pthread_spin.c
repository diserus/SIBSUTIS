#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int sh = 0;
pthread_spinlock_t lock;

void* my_thread0() {
    int i = 0;
    for (; i < 100; i++) {
        pthread_spin_lock(&lock);
        sh++;  
        pthread_spin_unlock(&lock);
    }
    return NULL;
}

void* my_thread1() {
    int i = 0;
    for (; i < 100; i++) {
        pthread_spin_lock(&lock);
        sh += 2;  
        pthread_spin_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];

    pthread_spin_init(&lock, PTHREAD_PROCESS_PRIVATE);

    pthread_create(&th_id[0], NULL, &my_thread0, NULL);
    pthread_create(&th_id[1], NULL, &my_thread1, NULL);

    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);

    pthread_spin_destroy(&lock);

    printf("%i\n", sh);

    return 0;
}
