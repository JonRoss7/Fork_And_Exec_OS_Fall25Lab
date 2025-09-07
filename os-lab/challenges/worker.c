#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("worker: ");
    for (int i = 0; i < argc; i++) {
        printf("argv[%d]=%s ", i, argv[i]);
    }
    
    char *myvar = getenv("MYVAR");
    if (myvar) {
        printf("and environment variable MYVAR=%s", myvar);
    }
    printf("\n");
    
    return 0;
}