//
// Created by Gregor Köhler on 1/12/24.
//
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(EXIT_SUCCESS);
    }

    FILE *fp;
    char *line = NULL;
    size_t len = 0;

    for (char **pargv = argv + 1; *pargv != argv[argc]; pargv++) {
        fp = fopen(*pargv, "r");
        if (fp == NULL) {
            fprintf(stdout, "wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }
        while (getline(&line, &len, fp) != -1) {
            printf("%s", line);
        }
        fclose(fp);
    }
}