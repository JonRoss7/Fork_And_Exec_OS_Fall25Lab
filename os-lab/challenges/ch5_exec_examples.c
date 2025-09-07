#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid1, pid2;
    
    // Child A uses execl
    pid1 = fork();
    if (pid1 == 0) {
        execl("/bin/echo", "echo", "one", "two", NULL);
        perror("execl failed");
        exit(1);
    } else if (pid1 < 0) {
        perror("fork failed");
        return 1;
    }
    
    // Child B uses execv
    pid2 = fork();
    if (pid2 == 0) {
        char *args[] = {"/bin/echo", "one", "two", NULL};
        execv("/bin/echo", args);
        perror("execv failed");
        exit(1);
    } else if (pid2 < 0) {
        perror("fork failed");
        return 1;
    }
    
    // Parent waits for both children
    int status;
    wait(&status);  // Wait for first child
    wait(&status);  // Wait for second child
    
    return 0;
}