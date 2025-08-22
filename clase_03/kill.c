#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void handle_signal(int sig) {
    printf("Hijo (%d): Recibí la señal %d, terminando...\n", getpid(), sig);
    exit(0);
}

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        printf("Hijo (%d): Estoy vivo, esperando...\n", getpid());
        signal(SIGTERM, handle_signal);
        while (1) {
            printf("Hijo (%d): Trabajando...\n", getpid());
            sleep(1);
        }
    } else {
        printf("Padre (%d): Creé un hijo con PID %d\n", getpid(), pid);
        sleep(10);
        printf("Padre (%d): Enviando SIGKILL al hijo (%d)\n", getpid(), pid);
        if (kill(pid, SIGKILL) == 0) {
            printf("Padre (%d): Señal enviada exitosamente\n", getpid());
        } else {
            perror("Error al enviar la señal");
        }

        wait(NULL);
        printf("Padre (%d): Hijo terminado\n", getpid());
    }

    return 0;
}
