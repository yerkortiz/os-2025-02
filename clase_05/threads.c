#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long n = 0;
pthread_mutex_t lock;
void *increment(void *arg);
void *decrement(void *arg);

int main(int argc, char *argv[]) {
    int numIters = atoi(argv[1]);
    pthread_t tid1, tid2;
    pthread_mutex_init(&lock, NULL);

    printf("MAIN STARTED\n");

    // instanciar un thread
    pthread_create(&tid1, NULL, increment, &numIters);
    pthread_create(&tid2, NULL, decrement, &numIters);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    printf("N = %lld\n", n);
    pthread_mutex_destroy(&lock);

    return 0;
}

void *increment(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&lock);
        ++n;
        pthread_mutex_unlock(&lock);
    }
    printf("Increment Thread: N = %lld\n", n);
    return NULL;
}

void *decrement(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&lock);
        --n;
        pthread_mutex_unlock(&lock);
    }
    printf("Decrement Thread: N = %lld\n", n);
    return NULL;
}
