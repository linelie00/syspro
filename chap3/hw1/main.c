#include <stdio.h>
#include <string.h>
#include "copy.h"

char lines[MAXLINES][MAXLINE];
int line_lengths[MAXLINES];

int main() {
    int main() {
    char lines[MAXLINES][MAXLINE];
    int line_lengths[MAXLINES];
    int count = 0;

    while (count < MAXLINES && fgets(lines[count], MAXLINE, stdin) != NULL) {
        line_lengths[count] = strlen(lines[count]);
        count++;
    }


    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (line_lengths[i] < line_lengths[j]) {

                int temp_len = line_lengths[i];
                line_lengths[i] = line_lengths[j];
                line_lengths[j] = temp_len;

                char temp_line[MAXLINE];
                copy(temp_line, lines[i]);
                copy(lines[i], lines[j]);
                copy(lines[j], temp_line);
            }
        }
    }

    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
    }

    return 0;
}
}

