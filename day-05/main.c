#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long start;
    long end;
} Range;

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

    Range ranges[256];
    size_t ranges_len = 0;

    long start, end;
    while(fscanf(f, "%ld-%ld", &start, &end) == 2) {
        ranges[ranges_len++] = (Range){start, end};
    }

    long id;
    while(fscanf(f, "%ld", &id) == 1) {
        for (size_t i = 0; i < ranges_len; i++) {
            if (id >= ranges[i].start && id <= ranges[i].end) {
                count++;
                break;
            }
        }
    }

    printf("--- Day 5: Cafeteria ---\n");
    printf("Answer for part 1: %d\n", count);

    fclose(f);
}
