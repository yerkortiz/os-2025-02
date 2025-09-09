#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdatomic.h>
long long n = 5;
atomic_bool flag[2] = {0, 0};
atomic_int turn = 0;
void *plus(void *arg);
void *minus(void *arg);
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
void *plus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {

        atomic_store(&flag[0], 1);
        atomic_thread_fence(memory_order_seq_cst);
        atomic_store(&turn, 1);
        atomic_thread_fence(memory_order_seq_cst);
        while (atomic_load(&flag[1]) && atomic_load(&turn) == 1) {

        }
        ++n;
        atomic_store(&flag[0], 0);
    }
    return NULL;
}
void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {

        atomic_store(&flag[1], 1);
        atomic_thread_fence(memory_order_seq_cst);
        atomic_store(&turn, 0);
        atomic_thread_fence(memory_order_seq_cst);
        while (atomic_load(&flag[0]) && atomic_load(&turn) == 0) {

        }

        --n;

        atomic_store(&flag[1], 0);
    }
    return NULL;
}
