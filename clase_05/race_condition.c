#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
long long n = 5;
int numIters;
void *plusOne(void *arg);
void *minusOne(void *arg);

int main(int argc, char *argv[]) {
    pthread_t pid, mid;
    numIters = atoi(argv[1]);
    printf("MAIN STARTED\n");
    pthread_create(&pid, NULL, &plusOne, NULL);
    pthread_create(&mid, NULL, &minusOne, NULL);
    pthread_join(pid, NULL);
    pthread_join(mid, NULL);
    printf("N = %lld", n);
    return 0;
}
void *plusOne(void *arg) {
    for(int i = 0; i < numIters; ++i)
        ++n;
    printf("%lld\n", n);
    return &n;
}
void *minusOne(void *arg) {
    for(int i = 0; i < numIters; ++i)
        --n;
    printf("%lld\n", n);
    return &n;
}
