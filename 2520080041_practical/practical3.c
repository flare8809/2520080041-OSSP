#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int pid = fork();

    if (pid == 0)
    {
        printf("Child: PID=%d, PPID=%d - Running\n", getpid(), getppid());

        sleep(5);
        printf("Child: PID=%d - Running again\n", getpid());

        sleep(5);
        printf("Child: Terminated\n");
    }
    else
    {
        printf("Parent: PID=%d, Child PID=%d - Running\n",
               getpid(), pid);

        printf("Parent: Waiting for child...\n");
        wait(NULL);

        printf("Parent: Child terminated, Parent running again\n");
    }

    return 0;
}