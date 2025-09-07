#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        char *args[] = {"ls", "-l", NULL};
        execvp(args[0], args);
        perror("execvp failed");
        _exit(1);
    } else {
        waitpid(pid, NULL, 0);
        printf("[parent] child finished exec.\n");
    }
    return 0;
}
