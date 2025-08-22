#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    int returnstatus1, returnstatus2, pid;
    int numbers[] = {1, 2, 3, 4, 5};
    int N = sizeof(numbers) / sizeof(numbers[0]);
    int suma = 0;

    returnstatus1 = pipe(pipe1);
    if (returnstatus1 == -1) {
        return 1;
    }

    returnstatus2 = pipe(pipe2);
    if (returnstatus2 == -1) {
        return 1;
    }

    pid = fork();
    if (pid == 0) {

        close(pipe1[1]);
        close(pipe2[0]);

        read(pipe1[0], &N, sizeof(N));
        int nums[N];
        read(pipe1[0], nums, sizeof(nums));

        for (int i = 0; i < N; i++) {
            suma += nums[i];
        }

        write(pipe2[1], &suma, sizeof(suma));

        close(pipe1[0]);
        close(pipe2[1]);
    } else {

        close(pipe1[0]);
        close(pipe2[1]);

        write(pipe1[1], &N, sizeof(N));
        write(pipe1[1], numbers, sizeof(numbers));

        read(pipe2[0], &suma, sizeof(suma));

        close(pipe1[1]);
        close(pipe2[0]);

        wait(NULL);
    }

    return 0;
}
