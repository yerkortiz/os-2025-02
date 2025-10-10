#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

enum { THINKING, HUNGRY, EATING } state[NUM_PHILOSOPHERS];
pthread_mutex_t mutex;
pthread_cond_t condition[NUM_PHILOSOPHERS];

void try_to_eat(int id) {
    int left = (id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    if (state[id] == HUNGRY && state[left] != EATING && state[right] != EATING) {
        state[id] = EATING;
        printf("Philosopher %d is EATING.\n", id + 1);
        pthread_cond_signal(&condition[id]);
    }
}

void pickup_forks(int id) {
    pthread_mutex_lock(&mutex);

    state[id] = HUNGRY;
    printf("Philosopher %d is HUNGRY.\n", id + 1);

    try_to_eat(id);

    while (state[id] != EATING) {
        pthread_cond_wait(&condition[id], &mutex);
    }

    pthread_mutex_unlock(&mutex);
}

void return_forks(int id) {
    int left = (id + NUM_PHILOSOPHERS - 1) % NUM_PHILOSOPHERS;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    pthread_mutex_lock(&mutex);

    state[id] = THINKING;
    printf("Philosopher %d is THINKING.\n", id + 1);

    try_to_eat(left);
    try_to_eat(right);

    pthread_mutex_unlock(&mutex);
}

void* philosopher(void* arg) {
    long id = (long)arg;

    while (1) {
        sleep(rand() % 3 + 1);
        pickup_forks(id);
        sleep(rand() % 3 + 1);
        return_forks(id);
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    long i;

    pthread_mutex_init(&mutex, NULL);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        state[i] = THINKING;
        pthread_cond_init(&condition[i], NULL);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, (void*)i);
    }

    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_cond_destroy(&condition[i]);
    }

    return 0;
}
