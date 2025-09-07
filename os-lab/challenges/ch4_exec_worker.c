#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - set environment variable and exec worker
        setenv("MYVAR", "hello", 1);
        execl("./worker", "worker", "arg1", "arg2", NULL);
        // If execl returns, it failed
        perror("execl failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process - wait for child
        int status;
        wait(&status);
    } else {
        // Fork failed
        perror("fork failed");
        return 1;
    }
    
    return 0;
}