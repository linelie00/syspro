#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t pid1, pid2;
    char buffer[1024];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return 1;
    }

    printf("parent process start\n");

    if ((pid1 = fork()) == 0) {
        close(pipefd[0]);
        printf("input string: ");
        fgets(buffer, sizeof(buffer), stdin);
        write(pipefd[1], buffer, strlen(buffer) + 1);
        close(pipefd[1]);
        return 0;
    }

    if ((pid2 = fork()) == 0) {
        close(pipefd[1]);
        read(pipefd[0], buffer, sizeof(buffer));
        close(pipefd[0]);

        for (int i = 0; buffer[i]; i++) {
            buffer[i] = toupper(buffer[i]);
        }
        printf("%s", buffer);
        return 0;
    }

    close(pipefd[0]);
    close(pipefd[1]);

    wait(NULL);
    wait(NULL);

    printf("Process finished with exit code 0\n");
    return 0;
}

