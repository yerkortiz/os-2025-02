#include<unistd.h>
#include<stdio.h>

int main() {
    // fork crea un proceso, al padre le retorna el pid del proceso hijo,
    // al hijo le retorna 0.
    int pid = fork();

    if(pid == 0) {
        printf("child process was created successfully %d\n", pid);
        printf("child process pid %d ppid %d\n", getpid(), getppid());
    } else if(pid > 0) {
        printf("parent process creates successfully %d\n", pid);
        printf("parent process pid %d ppid %d\n", getpid(), getppid());
    }
}
