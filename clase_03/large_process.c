#include<stdio.h>
#include <unistd.h>
int main() {
    printf("large process pid %d: ", getpid());
    while(1) {
        printf("working\n");
        sleep(1);
    }
    return 0;
}
