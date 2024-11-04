#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void printEnvVariable(const char *varName) {
    if (varName == NULL) {
        extern char **environ;
        for (char **env = environ; *env != NULL; env++) {
            printf("%s\n", *env);
        }
    } else {
        const char *value = getenv(varName);
        if (value) {
            printf("%s=%s\n", varName, value);
        } else {
            printf("Environment variable '%s' does not exist.\n", varName);
        }
    }
}

void printUserIds() {
    uid_t realUid = getuid();
    uid_t effectiveUid = geteuid();
    printf("My Realistic User ID: %d, My Valid  User ID: %d\n", realUid, effectiveUid);
}

void printGroupIds() {
    gid_t realGid = getgid();
    gid_t effectiveGid = getegid();
    printf("My Realistic Group ID: %d, My Valid Group ID: %d\n", realGid, effectiveGid);
}

void printProcessId() {
    printf("Process ID: %d\n", getpid());
}

void printParentProcessId() {
    printf("Parent Process ID: %d\n", getppid());
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-e [environment_variable]] | [-u] | [-g] | [-i] | [-p]\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-e") == 0) {
        if (argc == 3) {
            printEnvVariable(argv[2]);
        } else {
            printEnvVariable(NULL);
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        printUserIds();
    } else if (strcmp(argv[1], "-g") == 0) {
        printGroupIds();
    } else if (strcmp(argv[1], "-i") == 0) {
        printProcessId();
    } else if (strcmp(argv[1], "-p") == 0) {
        printParentProcessId();
    } else {
        fprintf(stderr, "Unknown option: %s\n", argv[1]);
        return 1;
    }

    return 0;
}

