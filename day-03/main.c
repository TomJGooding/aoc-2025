#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_joltage(const char *bank) {
    size_t bank_len = strlen(bank);

    int d1_max = 0;
    size_t d1_idx = 0;
    for (size_t i = 0; i < bank_len - 1; i++) {
        int digit = bank[i] - '0';
        if (digit > d1_max) {
            d1_max = digit;
            d1_idx = i;
        }
    }

    int d2_max = 0;
    for (size_t i = d1_idx + 1; i < bank_len; i++) {
        int digit = bank[i] - '0';
        if (digit > d2_max) {
            d2_max = digit;
        }
    }

    return (d1_max * 10) + d2_max;
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

    int total = 0;

    char bank[128];
    while (fgets(bank, sizeof(bank), f)) {
        bank[strlen(bank) - 1] = 0; // Remove newline
        total += max_joltage(bank);
    }

    printf("--- Day 3: Lobby ---\n");
    printf("Answer for part 1: %d\n", total);

    fclose(f);
}
