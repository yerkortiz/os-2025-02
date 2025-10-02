#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long n = 5;
pthread_mutex_t mutex;
pthread_cond_t cond;
int turn = 0;

void *plus(void *arg);
void *minus(void *arg);

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&pid, NULL, &plus, &numIters);
    pthread_create(&mid, NULL, &minus, &numIters);

    pthread_join(pid, NULL);
    pthread_join(mid, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    printf("N = %lld\n", n);
    return 0;
}

// suma cuando turno es 0
void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn != 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        ++n;
        turn = 1;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

// suma cuando turno es 1
void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn != 1) {
            pthread_cond_wait(&cond, &mutex);
        }
        --n;
        turn = 0;
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}
