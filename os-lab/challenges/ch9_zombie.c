#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - exit immediately
        printf("Child process (PID=%d) exiting immediately\n", getpid());
        exit(0);
    } else if (pid > 0) {
        // Parent process
        printf("Parent created child with PID=%d\n", pid);
        printf("Parent sleeping 10 seconds - child becomes zombie\n");
        
        sleep(10);
        
        printf("Parent calling wait() to clean up zombie\n");
        int status;
        wait(&status);
        printf("Zombie cleaned up, parent exiting\n");
        
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}