#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int sleep_times[] = {1, 2, 3};
    
    // Spawn 3 children
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        
        if (pids[i] == 0) {
            // Child process
            printf("Child %d starting, will sleep %d seconds\n", i + 1, sleep_times[i]);
            sleep(sleep_times[i]);
            printf("Child %d finished\n", i + 1);
            exit(0);
        } else if (pids[i] < 0) {
            perror("fork failed");
            return 1;
        }
    }
    
    // Parent polls with waitpid(-1, &status, WNOHANG)
    int children_finished = 0;
    while (children_finished < 3) {
        int status;
        pid_t finished_pid = waitpid(-1, &status, WNOHANG);
        
        if (finished_pid > 0) {
            printf("Parent detected child %d finished\n", finished_pid);
            children_finished++;
        } else if (finished_pid == 0) {
            // No child has finished yet
            printf("Parent polling... no children finished yet\n");
            usleep(500000);  // Sleep 0.5 seconds
        } else {
            perror("waitpid failed");
            break;
        }
    }
    
    printf("All children have finished\n");
    return 0;
}