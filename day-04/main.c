#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LINE_SIZE 256

int adjacent_rolls(size_t x, char *curr, char *prev, char *next) {
    assert(x < LINE_SIZE);

    int res = 0;

    if (x > 0) {
        res += (prev[x - 1] == '@');
        res += (curr[x - 1] == '@');
        res += (next[x - 1] == '@');
    }

    res += (prev[x] == '@');
    res += (next[x] == '@');

    res += (prev[x + 1] == '@');
    res += (curr[x + 1] == '@');
    res += (next[x + 1] == '@');

    return res;
}

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

    int count = 0;

    char prev[LINE_SIZE] = {0};
    char curr[LINE_SIZE] = {0};
    char next[LINE_SIZE] = {0};

    fgets(curr, sizeof(curr), f);
    while (fgets(next, sizeof(next), f)) {
        for (size_t x = 0; curr[x]; x++) {
            if (curr[x] == '@') {
                if (adjacent_rolls(x, curr, prev, next) < 4) {
                    count++;
                }
            }
        }

        strcpy(prev, curr);
        strcpy(curr, next);
    }

    // Finally check the last line
    memset(next, 0, sizeof(next));
    for (size_t x = 0; curr[x]; x++) {
        if (curr[x] == '@') {
            if (adjacent_rolls(x, curr, prev, next) < 4) {
                count++;
            }
        }
    }

    printf("--- Day 4: Printing Department ---\n");
    printf("Answer for part 1: %d\n", count);

    fclose(f);
}
