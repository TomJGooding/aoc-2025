#include <assert.h>
#include <limits.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BTNS 16

typedef unsigned long bitset;

#define bitset_set(bs, pos) (bs |= (1 << pos))
#define bitset_test(bs, pos) ((bs & (1 << pos)) != 0)

int bitset_count(bitset bs) {
    int count = 0;
    while (bs) {
        count += bs & 1;
        bs >>= 1;
    }

    return count;
}

bitset bitset_from_lights_diag(char *lights_diag) {
    bitset bs = 0;

    for (size_t i = 0; lights_diag[i]; i++) {
        if (lights_diag[i] == '#') {
            bitset_set(bs, i);
        }
    }

    return bs;
}

bitset bitset_from_btn_schem(char *btn_schem) {
    bitset bs = 0;
    char *saveptr;

    char *pos = strtok_r(btn_schem, "(,)", &saveptr);
    while (pos != NULL) {
        bitset_set(bs, atoi(pos));
        pos = strtok_r(NULL, "(,)", &saveptr);
    }

    return bs;
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

    int total_presses = 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        line[strlen(line) - 1] = 0; // Remove newline

        char *lights_diag = strtok(line, "[]");
        size_t n_bits = strlen(lights_diag);
        assert(n_bits < 32);
        bitset target_lights = bitset_from_lights_diag(lights_diag);

        bitset btns[MAX_BTNS];
        size_t btns_len = 0;

        char *token = strtok(NULL, " ");
        while (token != NULL) {
            if (token[0] == '(') {
                btns[btns_len++] = bitset_from_btn_schem(token);
            }
            token = strtok(NULL, " ");
        }

        int min_presses = INT_MAX;
        for (bitset pressed = 0; pressed < (1 << btns_len); pressed++) {
            bitset curr_lights = 0;
            for (size_t i = 0; i < btns_len; i++) {
                if (bitset_test(pressed, i)) {
                    curr_lights ^= btns[i];
                }
            }
            if (curr_lights == target_lights) {
                int presses = bitset_count(pressed);
                if (presses < min_presses) {
                    min_presses = presses;
                }
            }
        }
        total_presses += min_presses;
    }

    printf("--- Day 10: Factory ---\n");
    printf("Answer for part 1: %d\n", total_presses);

    fclose(f);
}
