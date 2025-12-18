#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

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

    long beams[MAX_LEN] = {0};

    int splits = 0;

    char line[MAX_LEN];
    while (fgets(line, sizeof(line), f)) {
        for (size_t i = 0; line[i]; i++) {
            if (line[i] == 'S') {
                beams[i] = 1;
                break;
            }
            if (line[i] == '^' && beams[i]) {
                if (i > 0) {
                    beams[i - 1] += beams[i];
                }
                if (i < strlen(line)) {
                    beams[i + 1] += beams[i];
                }
                beams[i] = 0;
                splits++;
            }
        }
    }

    long timelines = 0;
    for (size_t i = 0; i < MAX_LEN; i++) {
        timelines += beams[i];
    }

    printf("--- Day 7: Laboratories ---\n");
    printf("Answer for part 1: %d\n", splits);
    printf("Answer for part 2: %ld\n", timelines);

    fclose(f);
}
