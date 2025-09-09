#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
long long n = 5;
void *plusOne(void *arg);
void *minusOne(void *arg);

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    int numIters = atoi(argv[1]);
    pthread_create(&pid, NULL, &plusOne, &numIters);
    pthread_create(&mid, NULL, &minusOne, &numIters);
    pthread_join(pid, NULL);
    pthread_join(mid, NULL);
    printf("N = %lld", n);
    return 0;
}
void *plusOne(void *arg) {
    int numIters = *(int *)arg;
    for(int i = 0; i < numIters; ++i)
        ++n;
    printf("%lld\n", n);
    return &n;
}
void *minusOne(void *arg) {
    int numIters = *(int *)arg;
    for(int i = 0; i < numIters; ++i)
        --n;
    printf("%lld\n", n);
    return &n;
}
