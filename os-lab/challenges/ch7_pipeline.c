#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <pattern>\n", argv[0]);
        return 1;
    }
    
    char *pattern = argv[1];
    int pipefd[2];
    
    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe failed");
        return 1;
    }
    
    pid_t pid1 = fork();
    
    if (pid1 == 0) {
        // First child - run ls
        close(pipefd[0]);  // Close read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe write end
        close(pipefd[1]);
        
        execlp("ls", "ls", NULL);
        perror("execlp ls failed");
        exit(1);
        
    } else if (pid1 > 0) {
        pid_t pid2 = fork();
        
        if (pid2 == 0) {
            // Second child - run grep
            close(pipefd[1]);  // Close write end
            dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe read end
            close(pipefd[0]);
            
            execlp("grep", "grep", pattern, NULL);
            perror("execlp grep failed");
            exit(1);
            
        } else if (pid2 > 0) {
            // Parent - close pipe ends and wait for both children
            close(pipefd[0]);
            close(pipefd[1]);
            
            wait(NULL);  // Wait for first child
            wait(NULL);  // Wait for second child
            
        } else {
            perror("second fork failed");
            return 1;
        }
        
    } else {
        perror("first fork failed");
        return 1;
    }
    
    return 0;
}