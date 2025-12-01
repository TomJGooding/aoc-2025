#include <stdio.h>
#include <stdlib.h>

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

    const int steps = 100;
    int pos = 50;
    int count_p1 = 0;
    int count_p2 = 0;

    char rot;
    int dist;
    while (fscanf(f, " %c%d", &rot, &dist) == 2) {
        switch (rot) {
            case 'R':
                pos += dist;
                if (pos >= steps) {
                    count_p2 += pos / steps;
                    pos = pos % steps;
                }
                break;
            case 'L':
                pos -= dist;
                if (pos <= 0) {
                    count_p2 += abs(pos - steps) / steps;
                    // TODO: There is probably a smarter way to avoid double
                    // counting when the dial starts at zero
                    if (pos + dist == 0) {
                        count_p2--;
                    }
                    pos = ((pos % steps) + steps) % steps;
                }
                break;
        }
        if (pos == 0) {
            count_p1++;
        }
    }

    printf("--- Day 1: Secret Entrance ---\n");
    printf("Answer for part 1: %d\n", count_p1);
    printf("Answer for part 2: %d\n", count_p2);

    fclose(f);
}
