#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* funcionThread(void *arg) {
    pthread_mutex_lock(&lock);
    unsigned long i = 0;
    counter += 1;
    printf("\n Inicia job %d \n", counter);
    sleep(1);
    printf("\n Termina job %d \n", counter);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(void) {
    int i, err;
    pthread_mutex_init(&lock, NULL);
    for(i = 0; i < 2; ++i)
        err = pthread_create(&(tid[i]), NULL, &funcionThread, NULL);
    for(i = 0; i < 2; ++i)
        pthread_join(tid[i], NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
