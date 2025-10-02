#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

long long n = 5;
sem_t sem;

void *plus(void *arg);
void *minus(void *arg);

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);

    sem_init(&sem, 0, 1);

    pthread_create(&pid, NULL, &plus, &numIters);
    pthread_create(&mid, NULL, &minus, &numIters);

    pthread_join(pid, NULL);
    pthread_join(mid, NULL);

    sem_destroy(&sem);

    printf("N = %lld\n", n);
    return 0;
}

void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        sem_wait(&sem);
        ++n;
        sem_post(&sem);
    }
    return NULL;
}

void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        sem_wait(&sem);
        --n;
        sem_post(&sem);
    }
    return NULL;
}
