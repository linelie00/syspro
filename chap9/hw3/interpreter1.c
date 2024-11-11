#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    char *commands = argv[1];
    char *command = strtok(commands, ";");

    while (command != NULL) {
        pid_t pid;
        int status;
        char *args[100];
        char *redirect_in = NULL;
        char *redirect_out = NULL;
        int background = 0;

        if ((command[strlen(command) - 1] == '&')) {
            background = 1;
            command[strlen(command) - 1] = '\0'; // Remove the '&'
        }

        if ((redirect_in = strchr(command, '<')) != NULL) {
            *redirect_in = '\0';
            redirect_in = strtok(redirect_in + 1, " \t");
        }

        if ((redirect_out = strchr(command, '>')) != NULL) {
            *redirect_out = '\0';
            redirect_out = strtok(redirect_out + 1, " \t");
        }

        char *token = strtok(command, " \t");
        int i = 0;
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " \t");
        }
        args[i] = NULL;

        pid = fork();
        if (pid == 0) {
            if (redirect_in) {
                int in_fd = open(redirect_in, O_RDONLY);
                if (in_fd == -1) {
                    perror("Failed to open input file");
                    exit(1);
                }
                dup2(in_fd, STDIN_FILENO);
                close(in_fd);
            }

            if (redirect_out) {
                int out_fd = open(redirect_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (out_fd == -1) {
                    perror("Failed to open output file");
                    exit(1);
                }
                dup2(out_fd, STDOUT_FILENO);
                close(out_fd);
            }

            if (execvp(args[0], args) == -1) {
                perror("execvp failed");
                exit(1);
            }
        } else if (pid > 0) {
            if (!background) {
                wait(&status);
                printf("[%d] Child process %d terminated\n", getpid(), pid);
                printf("\tExit code: %d\n", WEXITSTATUS(status));
            } else {
                printf("Background process %d running...\n", pid);
            }
        } else {
            perror("fork failed");
            exit(1);
        }

        command = strtok(NULL, ";");
    }

    return 0;
}
