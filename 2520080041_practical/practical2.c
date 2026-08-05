#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    char command[100];

    printf("Enter a Linux command: ");
    if (scanf("%99s", command) != 1) {
        printf("Error reading input.\n");
        return 1;
    }

    pid_t pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        return 1;
    }
    else if (pid == 0) {
        // Child Process
        printf("Child Process - PID: %d, Parent PID: %d\n", getpid(), getppid());
        execlp(command, command, NULL);

        // If exec returns, an error occurred
        perror("Execution failed");
        exit(1);
    }
    else {
        // Parent Process
        printf("Parent Process - PID: %d, Child PID: %d\n", getpid(), pid);
        wait(NULL);
        printf("Child process finished.\n");
    }

    return 0;
}