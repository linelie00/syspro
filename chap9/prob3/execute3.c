#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int child, pid, status;
    pid = fork();
    if (pid == 0) { // Child process
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: Execution failed\n", argv[1]);
    } else { // Parent process
        child = wait(&status);
        printf("[%d] Child process %d terminated \n", getpid(), pid);
        printf("\tExit code %d \n", status >> 8);
    }
}

