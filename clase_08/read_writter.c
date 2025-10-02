#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_READERS 5
#define NUM_WRITERS 2

pthread_mutex_t mutex;
pthread_cond_t writer_condition;
int shared_data = 0;
int readers_count = 0;

void* reader(void* arg) {
    long id = (long)arg;

    while (1) {
        pthread_mutex_lock(&mutex);
        readers_count++;
        pthread_mutex_unlock(&mutex);

        printf("Reader %ld is reading data: %d\n", id, shared_data);
        sleep(1);

        pthread_mutex_lock(&mutex);
        readers_count--;
        if (readers_count == 0) {
            pthread_cond_signal(&writer_condition);
        }
        pthread_mutex_unlock(&mutex);

        sleep(rand() % 3);
    }
    return NULL;
}

void* writer(void* arg) {
    long id = (long)arg;
    int new_data;

    while (1) {
        pthread_mutex_lock(&mutex);
        while (readers_count > 0) {
            pthread_cond_wait(&writer_condition, &mutex);
        }

        new_data = rand() % 100;
        shared_data = new_data;
        printf("Writer %ld is writing data: %d\n", id, shared_data);

        pthread_mutex_unlock(&mutex);

        sleep(rand() % 4);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    long i;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&writer_condition, NULL);

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_create(&writers[i], NULL, writer, (void*)(i + 1));
    }
    for (i = 0; i < NUM_READERS; i++) {
        pthread_create(&readers[i], NULL, reader, (void*)(i + 1));
    }

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }
    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&writer_condition);

    return 0;
}
