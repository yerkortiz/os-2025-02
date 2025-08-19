#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("HIJO - PID: %d, PPID: %d\n", getpid(), getppid());
        sleep(1);
    } else {
        printf("PADRE - PID: %d, PID_HIJO: %d\n", getpid(), pid);
        wait(NULL);
        printf("Hijo terminó\n");
    }

    return 0;
}
