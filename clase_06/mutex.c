#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long n = 5;
pthread_mutex_t mutex;

void *plus(void *arg);
void *minus(void *arg);

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);

    pthread_mutex_init(&mutex, NULL);

    pthread_create(&pid, NULL, &plus, &numIters);
    pthread_create(&mid, NULL, &minus, &numIters);

    pthread_join(pid, NULL);
    pthread_join(mid, NULL);

    pthread_mutex_destroy(&mutex);

    printf("N = %lld\n", n);
    return 0;
}

void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&mutex);
        ++n;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&mutex);
        --n;
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
