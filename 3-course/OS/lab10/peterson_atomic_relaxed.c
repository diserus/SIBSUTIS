#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <unistd.h>
#include <time.h>
#include <bits/time.h>
#include <linux/time.h>
int sh = 0;
_Atomic int flag[2] = {0, 0};
_Atomic int turn = 0;

void* my_thread0(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        atomic_store_explicit(&flag[0], 1, memory_order_relaxed);
        atomic_store_explicit(&turn, 1, memory_order_relaxed);
        while (atomic_load_explicit(&flag[1], memory_order_relaxed) && 
               atomic_load_explicit(&turn, memory_order_relaxed) == 1);

        // Critical section
        sh++;

        atomic_store_explicit(&flag[0], 0, memory_order_relaxed);
        usleep(1);
    }
    return NULL;
}

void* my_thread1(void* arg) {
    int i = 0;
    for (; i < 100; i++) {
        atomic_store_explicit(&flag[1], 1, memory_order_relaxed);
        atomic_store_explicit(&turn, 0, memory_order_relaxed);
        while (atomic_load_explicit(&flag[0], memory_order_relaxed) && 
               atomic_load_explicit(&turn, memory_order_relaxed) == 0);

        // Critical section
        sh += 2;

        atomic_store_explicit(&flag[1], 0, memory_order_relaxed);
        usleep(100);
    }
    return NULL;
}

int main() {
    pthread_t th_id[2];
    struct timespec start, end;
    double elapsed;

    clock_gettime(CLOCK_MONOTONIC, &start);

    pthread_create(&th_id[0], NULL, &my_thread0, NULL);
    pthread_create(&th_id[1], NULL, &my_thread1, NULL);

    pthread_join(th_id[0], NULL);
    pthread_join(th_id[1], NULL);

    clock_gettime(CLOCK_MONOTONIC, &end);

    elapsed = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;

    printf("Result: %i (expected: 300)\n", sh);
    printf("Time: %.6f seconds\n", elapsed);
    return 0;
}
