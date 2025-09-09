#include <stdio.h>
#include <pthread.h>
#include <stdatomic.h>
#include <stdlib.h>

long long n = 5;

long long wait_loops = 0;
typedef struct {
    atomic_flag lock;
} spinlock_t;

void spinlock_init(spinlock_t *s) {
    atomic_flag_clear(&s->lock);
}

void spinlock_lock(spinlock_t *s) {
    while (atomic_flag_test_and_set(&s->lock)) {
        ++wait_loops;
    }
}

void spinlock_unlock(spinlock_t *s) {
    atomic_flag_clear(&s->lock);
}

void *plus(void *arg);
void *minus(void *arg);

spinlock_t spinlock;

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);

    spinlock_init(&spinlock);

    pthread_create(&pid, NULL, &plus, &numIters);
    pthread_create(&mid, NULL, &minus, &numIters);

    pthread_join(pid, NULL);
    pthread_join(mid, NULL);

    printf("N = %lld\n", n);
    printf("WAIT TIME %lld", wait_loops);
    return 0;
}

void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        spinlock_lock(&spinlock);
        ++n;
        spinlock_unlock(&spinlock);
    }
    return NULL;
}

void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        spinlock_lock(&spinlock);
        --n;
        spinlock_unlock(&spinlock);
    }
    return NULL;
}
