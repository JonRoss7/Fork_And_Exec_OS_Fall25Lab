#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process
        printf("Hello from child (PID=%d, PPID=%d)\n", getpid(), getppid());
        sleep(2);
        exit(7);
    } else if (pid > 0) {
        // Parent process
        int status;
        wait(&status);
        printf("child %d exited with status %d\n", pid, WEXITSTATUS(status));
    } else {
        // Fork failed
        perror("fork failed");
        return 1;
    }
    
    return 0;
}