#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long max_joltage(const char *bank, size_t bats) {
    long res = 0;

    size_t bank_len = strlen(bank);

    assert(bats > 0);
    assert(bats <= bank_len);

    int max = 0;
    int max_idx = 0;
    for (size_t bat_n = 1; bat_n <= bats; bat_n++) {
        size_t bats_rem = bats - bat_n;
        for (size_t i = max_idx; i < bank_len - bats_rem; i++) {
            int digit = bank[i] - '0';
            if (digit > max) {
                max = digit;
                max_idx = i;
            }
        }
        res = res * 10 + max;
        max = 0;
        max_idx += 1;
    }

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

    long total_p1 = 0;
    long total_p2 = 0;

    char bank[128];
    while (fgets(bank, sizeof(bank), f)) {
        bank[strlen(bank) - 1] = 0; // Remove newline
        total_p1 += max_joltage(bank, 2);
        total_p2 += max_joltage(bank, 12);
    }

    printf("--- Day 3: Lobby ---\n");
    printf("Answer for part 1: %ld\n", total_p1);
    printf("Answer for part 2: %ld\n", total_p2);

    fclose(f);
}
