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

    char *ops_line = lines[lines_read - 1];

    long grand_total_p1 = 0;

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

            grand_total_p1 += total;
        }
    }

    long grand_total_p2 = 0;

    /*
     * This might not be the most efficient solution, but it avoids
     * trying to parse the problems from right-to-left!
     */
    size_t op_idx = 0;
    for (size_t ox = 1; ops_line[ox]; ox++) {
        if (ops_line[ox] == '+' || ops_line[ox] == '*' || ops_line[ox] == '\n') {
            long total = (ops_line[op_idx] == '*') ? 1 : 0;

            size_t col_end = (ops_line[ox] == '\n') ? ox : ox - 1;
            for (size_t nx = op_idx; nx < col_end; nx++) {
                char num_str[MAX_LINES];
                for (size_t y = 0; y < lines_read; y++) {
                    num_str[y] = lines[y][nx];
                }
                num_str[lines_read] = 0;
                int num = atoi(num_str);
                total = (ops_line[op_idx] == '*') ? total * num : total + num;
            }

            grand_total_p2 += total;
            op_idx = ox;
        }
    }

    printf("--- Day 6: Trash Compactor ---\n");
    printf("Answer for part 1: %ld\n", grand_total_p1);
    printf("Answer for part 2: %ld\n", grand_total_p2);
}
