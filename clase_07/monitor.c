#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

long long n = 5;

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t cond_plus;
    pthread_cond_t cond_minus;
    int turn; // 0 para plus, 1 para minus
} Monitor;

Monitor monitor = {
    PTHREAD_MUTEX_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    PTHREAD_COND_INITIALIZER,
    0
};

void enter_plus() {
    pthread_mutex_lock(&monitor.mutex);
    while (monitor.turn != 0) {
        pthread_cond_wait(
            &monitor.cond_plus,
            &monitor.mutex
        );
    }
}

void exit_plus() {
    monitor.turn = 1;
    pthread_cond_signal(&monitor.cond_minus);
    pthread_mutex_unlock(&monitor.mutex);
}

void enter_minus() {
    pthread_mutex_lock(&monitor.mutex);
    while (monitor.turn != 1) {
        pthread_cond_wait(
            &monitor.cond_minus,
            &monitor.mutex
        );
    }
}

void exit_minus() {
    monitor.turn = 0;
    pthread_cond_signal(&monitor.cond_plus);
    pthread_mutex_unlock(&monitor.mutex);
}

void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        enter_plus();
        ++n;
        exit_plus();
    }
    return NULL;
}

void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        enter_minus();
        --n;
        exit_minus();
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);

    pthread_create(&pid, NULL, &plus, &numIters);
    pthread_create(&mid, NULL, &minus, &numIters);

    pthread_join(pid, NULL);
    pthread_join(mid, NULL);

    printf("N = %lld\n", n);
    return 0;
}
