#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/wait.h>

void low_up(char *s) {
    for(; *s != '\0'; ++s)
        if(isalpha(*s))
            *s = (islower(*s)) ? toupper(*s) : tolower(*s);
}

int main() {
    int pipe1[2];
    int returnstatus, pid;
    char sl2[20] = {"BueNas TarDeS"};
    char sl1[20];

    returnstatus = pipe(pipe1);
    if (returnstatus == -1) {
        printf("ERROR\n");
        return 1;
    }

    pid = fork();
    if (pid == 0) {
        close(pipe1[1]);
        read(pipe1[0], sl1, sizeof(sl1));
        low_up(sl1);
        printf("El hijo saluda: %s Padre\n", sl1);
        close(pipe1[0]);
    } else {
        close(pipe1[0]);
        printf("El padre saluda: %s Hijo\n", sl2);
        write(pipe1[1], sl2, sizeof(sl2));
        close(pipe1[1]);
        wait(NULL);
    }
    return 0;
}
