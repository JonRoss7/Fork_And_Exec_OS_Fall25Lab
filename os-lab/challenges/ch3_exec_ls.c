#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - execute ls -la
        execlp("ls", "ls", "-la", NULL);
        // If execlp returns, it failed
        perror("execlp failed");
        exit(1);
    } else if (pid > 0) {
        // Parent process - wait for child
        int status;
        wait(&status);
        printf("Child process finished, parent continuing...\n");
    } else {
        // Fork failed
        perror("fork failed");
        return 1;
    }
    
    return 0;
}