#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number_of_children>\n", argv[0]);
        return 1;
    }
    
    int N = atoi(argv[1]);
    
    // Fork N children
    for (int i = 0; i < N; i++) {
        pid_t pid = fork();
        
        if (pid == 0) {
            // Child process
            printf("Child %d (PID=%d)\n", i, getpid());
            exit(i + 1);  // Exit with code equal to index+1
        } else if (pid < 0) {
            perror("fork failed");
            return 1;
        }
        // Parent continues to next iteration
    }
    
    // Parent waits for all children
    for (int i = 0; i < N; i++) {
        int status;
        pid_t child_pid = wait(&status);
        printf("Child PID %d finished with status %d\n", child_pid, WEXITSTATUS(status));
    }
    
    return 0;
}