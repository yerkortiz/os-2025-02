#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
long long n = 5;
bool flag[2] = {false, false};
int turn = 0;
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
        flag[0] = true;
        turn = 1;
        while (flag[1] && turn == 1) {
        }
        ++n;
        flag[0] = false;
    }
    return NULL;
}
void *minus(void *arg) {
    int numIters = *(int *)arg;
    for (int i = 0; i < numIters; ++i) {
        flag[1] = true;
        turn = 0;
        while (flag[0] && turn == 0) {
        }
        --n;
        flag[1] = false;
    }
    return NULL;
}
