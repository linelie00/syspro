#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define MAXARG 100

int main() {
    char input[1024];
    char *args[MAXARG];
    pid_t pid;
    int background;
    char *token, *saveptr;

    while (1) {
        printf("Shell> ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            if (feof(stdin)) {
                printf("\nExiting shell...\n");
                break;
            }
            perror("fgets failed");
            continue;
        }

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0) {
            continue;
        }

        background = 0;
        if (input[strlen(input) - 1] == '&') {
            background = 1;
            input[strlen(input) - 1] = '\0';
        }

        token = strtok_r(input, " \t", &saveptr);
        int i = 0;
        while (token != NULL && i < MAXARG - 1) {
            args[i++] = token;
            token = strtok_r(NULL, " \t", &saveptr);
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("execvp failed");
                exit(1);
            }
        } else if (pid > 0) {
            if (!background) {
                wait(NULL);
            } else {
                printf("Background process %d running...\n", pid);
            }
        } else {
            perror("fork failed");
            exit(1);
        }
    }

    return 0;
}

