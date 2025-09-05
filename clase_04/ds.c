#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void binaryTree(int current_height, int max_height) {
    if (current_height > max_height) {
        return;
    }

    if (!fork() || !fork()) {
        binaryTree(current_height + 1, max_height);
        exit(0);
    }

    wait(NULL);
    wait(NULL);
}

void processList(int current, int N) {
    if (current >= N) {
        return;
    }

    if (fork() == 0) {
        processList(current + 1, N);
        exit(0);
    }

    wait(NULL);
}

void star(int current, int N) {
    if (current >= N) {
        return;
    }

    if (fork() == 0) {
        exit(0);
    }

    star(current + 1, N);

    wait(NULL);
}

void f1() {
    int p=0, c = 0;
    if(fork() && fork()) {
        p++;
        printf("p=%d\n", p);
    } else {
        c++;
        printf("c=%d\n", c);
    }
}

void f2() {
    int p=0, c = 0;
    if(fork() || fork()) {
        p++;
        printf("p=%d\n", p);
    } else {
        c++;
        printf("c=%d\n", c);
    }
}
int main() {
    f1();
    return 0;
}
