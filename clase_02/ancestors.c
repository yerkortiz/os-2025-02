#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void get_parent_info(pid_t pid, pid_t *ppid, char *name) {
    char command[100], buffer[100];
    FILE *fp;

    sprintf(command, "ps -o ppid= -p %d", pid);
    fp = popen(command, "r");
    if (fp && fscanf(fp, "%d", ppid) == 1) {
        pclose(fp);
    } else {
        *ppid = -1;
        if (fp) pclose(fp);
    }

    sprintf(command, "ps -o comm= -p %d", pid);
    fp = popen(command, "r");
    if (fp && fgets(buffer, sizeof(buffer), fp)) {
        // Limpiar salto de línea
        buffer[strcspn(buffer, "\n")] = 0;
        strcpy(name, buffer);
        pclose(fp);
    } else {
        strcpy(name, "unknown");
        if (fp) pclose(fp);
    }
}

int main() {
    pid_t current = getpid();
    pid_t ppid;
    char name[50];

    printf("=== Cadena Completa de Ancestros ===\n");

    while (current > 0) {
        get_parent_info(current, &ppid, name);

        printf("PID: %d, Nombre: %s", current, name);
        if (current != 1) {
            printf(" -> Padre: %d", ppid);
        }
        printf("\n");

        if (current == 1 || ppid <= 0) {
            break;
        }

        current = ppid;
    }

    return 0;
}
