#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid_t pid = fork();
    
    if (pid == 0) {
        // Child process - read from pipe and calculate sum
        close(pipefd[1]);  // Close write end
        
        int num, sum = 0;
        while (read(pipefd[0], &num, sizeof(int)) > 0) {
            sum += num;
        }
        close(pipefd[0]);  // Close read end
        
        printf("Sum = %d.\n", sum);
        exit(0);
        
    } else if (pid > 0) {
        // Parent process - write numbers 1-10 to pipe
        close(pipefd[0]);  // Close read end
        
        for (int i = 1; i <= 10; i++) {
            write(pipefd[1], &i, sizeof(int));
        }
        close(pipefd[1]);  // Close write end
        
        wait(NULL);  // Wait for child
        
    } else {
        perror("fork failed");
        return 1;
    }
    
    return 0;
}