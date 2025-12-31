#include <iostream>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in = 0;   
int out = 0; 

sem_t full, empty;
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 10; i++) {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        
        int item = rand() % 100;
        buffer[in] = item;
        std::cout << "Producer " << id << " produced: " << item 
                  << " at index " << in << std::endl;
        in = (in + 1) % BUFFER_SIZE;  
        
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
    return nullptr;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < 10; i++) {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        
        int item = buffer[out];
        std::cout << "Consumer " << id << " consumed: " << item 
                  << " from index " << out << std::endl;
        out = (out + 1) % BUFFER_SIZE;  
        
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
    return nullptr;
}

int main() {
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, nullptr);
    
    pthread_t prod, cons;
    int prod_id = 1, cons_id = 1;
    
    pthread_create(&prod, nullptr, producer, &prod_id);
    pthread_create(&cons, nullptr, consumer, &cons_id);
    
    pthread_join(prod, nullptr);
    pthread_join(cons, nullptr);
    
    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    
    return 0;
}
