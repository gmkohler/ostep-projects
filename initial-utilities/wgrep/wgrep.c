//
// Created by Gregor Köhler on 1/12/24.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    }

    char *pattern = argv[1];
    size_t pattern_length = strlen(pattern);

    int is_using_stdin = argc == 2;
    FILE *stream;
    char *line = NULL;
    size_t len = 0;

    if (is_using_stdin) {
        stream = stdin;
    } else {
        stream = fopen(argv[2], "r");
        if (stream == NULL) {
            fprintf(stdout, "wgrep: cannot open file\n");
            exit(EXIT_FAILURE);
        }
    }

    while (getline(&line, &len, stream) != -1) {
        if (pattern_length > len) {
            continue; // can't be a substring if strlen(pattern) > strlen(line)
        }

        if (strstr(line, pattern) != NULL) {
            printf("%s", line);
        }
    }

    if (!is_using_stdin) {
        fclose(stream);
    }

    exit(EXIT_SUCCESS);
}
