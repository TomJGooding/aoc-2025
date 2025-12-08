#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    long start;
    long end;
} Range;

int compare_ranges(const void *p1, const void *p2) {
    Range *range1 = (Range *)p1;
    Range *range2 = (Range *)p2;

    if (range1->start != range2->start) {
        return (range1->start < range2->start) ? -1 : 1;
    }

    if (range1->end != range2->end) {
        return (range1->end < range2->end) ? -1 : 1;
    }

    return 0;
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

    Range ranges[256];
    size_t ranges_len = 0;

    long start, end;
    while(fscanf(f, "%ld-%ld", &start, &end) == 2) {
        ranges[ranges_len++] = (Range){start, end};
    }

    int count_p1 = 0;

    long id;
    while(fscanf(f, "%ld", &id) == 1) {
        for (size_t i = 0; i < ranges_len; i++) {
            if (id >= ranges[i].start && id <= ranges[i].end) {
                count_p1++;
                break;
            }
        }
    }

    // Sort the ranges by start then by end
    qsort(ranges, ranges_len, sizeof(Range), compare_ranges);

    long count_p2 = ranges[0].end - ranges[0].start + 1;

    Range prev_range = ranges[0];
    for (size_t i = 1; i < ranges_len; i++) {
        if (ranges[i].start > prev_range.end) {
            // No overlap
            count_p2 += ranges[i].end - ranges[i].start + 1;

            prev_range = ranges[i];
        } else if (ranges[i].end > prev_range.end) {
            long start = prev_range.end + 1;
            long end = ranges[i].end;
            count_p2 += end - start + 1;

            prev_range.end = end;
        }
    }

    printf("--- Day 5: Cafeteria ---\n");
    printf("Answer for part 1: %d\n", count_p1);
    printf("Answer for part 2: %ld\n", count_p2);

    fclose(f);
}
