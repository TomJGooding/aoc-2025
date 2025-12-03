#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_invalid_p1(long id) {
    char id_str[32];
    int len;
    len = snprintf(id_str, sizeof(id_str), "%ld", id);

    if (len % 2 == 0) {
        int half = len / 2;
        if (strncmp(id_str, id_str + half, half) == 0) {
            return true;
        }
    }

    return false;
}

bool is_invalid_p2(long id) {
    char id_str[32];
    int len;
    len = snprintf(id_str, sizeof(id_str), "%ld", id);

    for (int chunks = 2; chunks <= len; chunks++) {
        if (len % chunks != 0) {
            continue;
        }

        int chunk_len = len / chunks;
        int repeats = 1;
        for (int i = 1; i < chunks; i++) {
            if (strncmp(id_str, id_str + (i * chunk_len), chunk_len) == 0) {
                repeats++;
            } else {
                break;
            }
        }

        if (repeats == chunks) {
            return true;
        }
    }

    return false;
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

    long invalid_sum_p1 = 0;
    long invalid_sum_p2 = 0;

    long first_id;
    long last_id;
    while(fscanf(f, "%ld-%ld,", &first_id, &last_id) == 2) {
        for (long id = first_id; id <= last_id; id++) {
            if (is_invalid_p1(id)) {
                invalid_sum_p1 += id;
            }
            if (is_invalid_p2(id)) {
                invalid_sum_p2 += id;
            }
        }
    }

    printf("--- Day 2: Gift Shop ---\n");
    printf("Answer for part 1: %ld\n", invalid_sum_p1);
    printf("Answer for part 2: %ld\n", invalid_sum_p2);

    fclose(f);
}
