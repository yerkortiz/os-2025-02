#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
    pid_t child_pid = fork();
    if (child_pid > 0) {
        printf("Padre esperando... PID hijo: %d\n", child_pid);
        sleep(10);
        wait(NULL);
        printf("ZOMBIE EXTERMINADO\n");
    } else if(child_pid == 0) {
        printf("ZOMBIE ID %d\n", getpid());
        exit(0);
    }
    return 0;
}
