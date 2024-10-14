#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_file(FILE *fp, int line_numbers) {
    int c;
    int line_count = 1;

    if (line_numbers) {
        printf("%d: ", line_count);
    }

    while ((c = getc(fp)) != EOF) {
        putc(c, stdout);
        if (c == '\n') {
            line_count++;
            if (line_numbers) {
                printf("%d: ", line_count);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *fp;

    if (argc < 2) {
        fp = stdin;
        print_file(fp, 0);
    } else {
        int line_numbers = 0;

        if (strcmp(argv[1], "-n") == 0) {
            line_numbers = 1;
            argv++;
            argc--;
        }

        for (int i = 1; i < argc; i++) {
            if ((fp = fopen(argv[i], "r")) == NULL) {
                fprintf(stderr, "Error opening file: %s\n", argv[i]);
                continue;
            }
            print_file(fp, line_numbers);
            fclose(fp);
        }
    }

    return 0;
}

