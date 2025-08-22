#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<signal.h>

int main() {
    pid_t child_pid = fork();

    if(child_pid < 0) {
        perror("fork failed");
        exit(EXIT_FAILURE);
    } else if(child_pid == 0) {
        while(1) {
            printf("doing important stuff\n");
            sleep(5);
        }
    } else {
         kill(child_pid, SIGKILL);
    }
}
