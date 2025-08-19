#include <stdio.h>
// Program that receives an array of arguments as input
// and as output it returns the same arguments
int main(int argc, char** argv) {
    printf("Quantity of arguments %d\n", argc);
    for (int i = 0; i < argc; i++) {
            printf("Arg %d: %s\n", i, argv[i]);
        }
    return 0;
}
