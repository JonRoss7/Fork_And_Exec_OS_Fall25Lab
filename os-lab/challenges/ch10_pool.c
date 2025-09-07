#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

void process_file(const char *filename) {
    printf("Worker PID %d processing file: %s\n", getpid(), filename);
    // Simulate work by sleeping
    sleep(2);
    printf("Worker PID %d finished processing: %s\n", getpid(), filename);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <concurrency_limit> <file1> <file2> ...\n", argv[0]);
        return 1;
    }
    
    int M = atoi(argv[1]);  // Concurrency limit
    int total_files = argc - 2;
    char **files = &argv[2];
    
    int active_workers = 0;
    int files_processed = 0;
    int next_file = 0;
    
    printf("Processing %d files with concurrency limit %d\n", total_files, M);
    
    while (files_processed < total_files) {
        // Spawn new workers if under limit and files remaining
        while (active_workers < M && next_file < total_files) {
            pid_t pid = fork();
            
            if (pid == 0) {
                // Child worker process
                process_file(files[next_file]);
                exit(0);
            } else if (pid > 0) {
                printf("Started worker PID %d for file: %s\n", pid, files[next_file]);
                active_workers++;
                next_file++;
            } else {
                perror("fork failed");
                return 1;
            }
        }
        
        // Wait for at least one worker to finish
        int status;
        pid_t finished_pid = wait(&status);
        if (finished_pid > 0) {
            printf("Worker PID %d finished\n", finished_pid);
            active_workers--;
            files_processed++;
        }
    }
    
    // Wait for any remaining workers
    while (active_workers > 0) {
        int status;
        pid_t finished_pid = wait(&status);
        if (finished_pid > 0) {
            printf("Final worker PID %d finished\n", finished_pid);
            active_workers--;
        }
    }
    
    printf("All files processed\n");
    return 0;
}