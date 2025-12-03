#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool is_invalid_id(long id) {
    bool res = false;

    char id_str[32];
    int len;
    len = snprintf(id_str, sizeof(id_str), "%ld", id);

    if (len % 2 == 0) {
        int half = len / 2;
        if (strncmp(id_str, id_str + half, half) == 0) {
            res = true;
        }
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

    long invalid_sum = 0;

    long first_id;
    long last_id;
    while(fscanf(f, "%ld-%ld,", &first_id, &last_id) == 2) {
        for (long id = first_id; id <= last_id; id++) {
            if (is_invalid_id(id)) {
                invalid_sum += id;
            }
        }
    }

    printf("--- Day 2: Gift Shop ---\n");
    printf("Answer for part 1: %ld\n", invalid_sum);

    fclose(f);
}
