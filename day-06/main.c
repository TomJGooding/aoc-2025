#include <stdio.h>
#include <stdlib.h>

#define MAX_LEN 4096
#define MAX_LINES 8

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Missing input file argument\n");
        exit(1);
    }

    const char *fname = argv[1];
    FILE *f = fopen(fname, "r");
    if (f == NULL) {
        fprintf(stderr, "Cannot open '%s'\n", fname);
        exit(1);
    }

    char lines[MAX_LINES][MAX_LEN];
    size_t lines_read = 0;
    while (lines_read < MAX_LINES && fgets(lines[lines_read], MAX_LEN, f)) {
        lines_read++;
    }

    fclose(f);

    long grand_total = 0;

    char *ops_line = lines[lines_read - 1];
    for (size_t x = 0; ops_line[x]; x++) {
        if (ops_line[x] == '+' || ops_line[x] == '*') {
            char op = ops_line[x];
            long total = (op == '*') ? 1 : 0;

            for (size_t y = 0; y < lines_read - 1; y++) {
                long num;
                if (sscanf(lines[y] + x, "%ld", &num) == 1) {
                    total = (op == '*') ? total * num : total + num;
                }
            }

            grand_total += total;
        }
    }

    printf("--- Day 6: Trash Compactor ---\n");
    printf("Answer for part 1: %ld\n", grand_total);
}
