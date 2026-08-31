#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid[3];
    int i, status;

    for (i = 0; i < 3; i++) {
        pid[i] = fork();
        if (pid[i] < 0) {
            perror("fork failed");
            exit(1);
        }
        if (pid[i] == 0) {
            printf("Child %d started\n", i + 1);
            printf("PID : %d\n", getpid());
            printf("PPID : %d\n", getppid());
            sleep(i + 2);
            printf("Child %d finished\n\n", i + 1);
            exit(0);
        }
    }

    printf("Parent PID: %d\n\n", getpid());
    
    printf("Using wait():\n");
    for (i = 0; i < 2; i++) {
        wait(&status);
        printf("A child process terminated.\n");
    }

    printf("\nUsing waitpid():\n");
    waitpid(pid[2], &status, 0);
    printf("Child with PID %d terminated.\n", pid[2]);

    printf("\nAll child processes completed.\n");
    return 0;
}