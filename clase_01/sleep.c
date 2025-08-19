#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    printf("%ld %ld\n", (long)getpid(), (long)getppid());

    sleep(20);
    return 0;
}
