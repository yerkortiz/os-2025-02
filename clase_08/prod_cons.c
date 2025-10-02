#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_LOAD 20

int buffer[BUFFER_SIZE];
int cont = 0;
int buffer_in = 0;
int buffer_out = 0;

pthread_mutex_t mutex;
pthread_cond_t full_cond;
pthread_cond_t empty_cond;

void *producer(void *arg) {
    int item;
    for (int i = 0; i < ITEMS_LOAD; i++) {
        item = i;

        pthread_mutex_lock(&mutex);

        while (cont == BUFFER_SIZE) {
            printf("producer: full buffer, waiting...\n");
            pthread_cond_wait(&full_cond, &mutex);
        }

        buffer[buffer_in] = item;
        printf("producer produces -> %d at position %d\n", item, buffer_in);
        buffer_in = (buffer_in + 1) % BUFFER_SIZE;
        cont++;

        pthread_cond_signal(&empty_cond);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;
    for (int i = 0; i < ITEMS_LOAD; i++) {
        pthread_mutex_lock(&mutex);

        while (cont == 0) {
            printf("consumer: empty buffer, waiting...\n");
            pthread_cond_wait(&empty_cond, &mutex);
        }

        item = buffer[buffer_out];
        printf("consumer consumes <- %d from position %d\n", item, buffer_out);
        buffer_out = (buffer_out + 1) % BUFFER_SIZE;
        cont--;
        pthread_cond_signal(&full_cond);

        pthread_mutex_unlock(&mutex);

        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t id_producer, id_consumer;

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&full_cond, NULL);
    pthread_cond_init(&empty_cond, NULL);

    if (pthread_create(&id_producer, NULL, producer, NULL) != 0) {
        exit(EXIT_FAILURE);
    }
    if (pthread_create(&id_consumer, NULL, consumer, NULL) != 0) {
        exit(EXIT_FAILURE);
    }

    pthread_join(id_producer, NULL);
    pthread_join(id_consumer, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&full_cond);
    pthread_cond_destroy(&empty_cond);

    return 0;
}
