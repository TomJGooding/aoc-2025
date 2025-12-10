#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

    // TODO: A bitset would be more efficient!
    bool beams[256] = {0};

    int splits = 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        for (size_t i = 0; line[i]; i++) {
            if (line[i] == 'S') {
                beams[i] = true;
                break;
            }
            if (line[i] == '^' && beams[i]) {
                beams[i] = false;
                if (i > 0) {
                    beams[i - 1] = true;
                }
                if (i < strlen(line)) {
                    beams[i + 1] = true;
                }
                splits++;
            }
        }
    }

    printf("--- Day 7: Laboratories ---\n");
    printf("Answer for part 1: %d\n", splits);

    fclose(f);
}
