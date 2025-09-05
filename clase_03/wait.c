#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main() {
    int pid = fork();
    if(pid == 0) {
        printf("child process pid %d ppid %d\n", getpid(), getppid());
    } else if(pid > 0) {
        wait(NULL);
        printf("parent process pid %d ppid %d\n", getpid(), getppid());
    }
}
