#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    char str[1024];
    char *command1, *command2;
    int fd[2];
    pid_t pid1, pid2;

    printf("[shell] ");
    fgets(str, sizeof(str), stdin);
    str[strlen(str) - 1] = '\0';

    if (strchr(str, '|') != NULL) {
        command1 = strtok(str, "| ");
        command2 = strtok(NULL, "| ");
    } else {
        fprintf(stderr, "Error: Pipe (|) is required in the command.\n");
        return 1;
    }

    if (pipe(fd) == -1) {
        perror("pipe");
        return 1;
    }

    if ((pid1 = fork()) == 0) {
        close(fd[READ]);
        dup2(fd[WRITE], STDOUT_FILENO);
        close(fd[WRITE]);
        execlp(command1, command1, NULL);
        perror("execlp");
        exit(1);
    }

    if ((pid2 = fork()) == 0) {
        close(fd[WRITE]);
        dup2(fd[READ], STDIN_FILENO);
        close(fd[READ]);
        execlp(command2, command2, NULL);
        perror("execlp");
        exit(1);
    }

    close(fd[READ]);
    close(fd[WRITE]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}

