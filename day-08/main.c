#include <assert.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_COORDS 1000
#define MAX_PAIRS (MAX_COORDS * (MAX_COORDS - 1) / 2)

// For the example in part 1, change connections to 10
#define CONNECTIONS 1000

typedef struct {
    int x;
    int y;
    int z;
} Coord;

typedef struct {
    size_t coord1_idx;
    size_t coord2_idx;
    double dist;
} CoordPair;

typedef struct {
    size_t coord_idxs[CONNECTIONS];
    size_t len;
} Circuit;

double distance(Coord p, Coord q) {
    double dx = p.x - q.x;
    double dy = p.y - q.y;
    double dz = p.z - q.z;
    return sqrt((dx * dx) + (dy * dy) + (dz * dz));
}

int compare_pair_dist(const void *p1, const void *p2) {
    double dist1 = ((CoordPair *)p1)->dist;
    double dist2 = ((CoordPair *)p2)->dist;

    if (dist1 != dist2) {
        return (dist1 < dist2) ? -1 : 1;
    }
    return 0;
}

int compare_circuit_len_reversed(const void *p1, const void *p2) {
    size_t len1 = ((Circuit *)p1)->len;
    size_t len2 = ((Circuit *)p2)->len;

    if (len1 != len2) {
        return (len1 > len2) ? -1 : 1;
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

    Coord coords[MAX_COORDS];
    size_t coords_len = 0;

    int x, y, z;
    while (fscanf(f, "%d,%d,%d", &x, &y, &z) == 3) {
        coords[coords_len++] = (Coord){x, y, z};
    }

    fclose(f);

    /* 
     * TODO: There must be a more efficient way than checking all the
     * possible distances and then sorting them?
     */
    CoordPair *pairs = malloc(MAX_PAIRS * sizeof(CoordPair));
    assert(pairs != NULL);
    size_t pairs_len = 0;

    for (size_t i = 0; i < coords_len - 1; i++) {
        for (size_t j = i + 1; j < coords_len; j++) {
            double dist = distance(coords[i], coords[j]);
            pairs[pairs_len++] = (CoordPair) {
                .coord1_idx = i,
                .coord2_idx = j,
                .dist = dist
            };
        }
    }

    qsort(pairs, pairs_len, sizeof(CoordPair), compare_pair_dist);

    size_t coord_in_circuit[MAX_COORDS];
    Circuit *circuits = malloc(MAX_COORDS * sizeof(Circuit));
    assert(circuits != NULL);

    for (size_t i = 0; i < coords_len; i++) {
        coord_in_circuit[i] = i;
        circuits[i] = (Circuit){.coord_idxs = {i}, .len = 1};
    }
    size_t circuits_len = coords_len;

    for (size_t i = 0; i < CONNECTIONS; i++) {
        size_t circuit1_idx = coord_in_circuit[pairs[i].coord1_idx];
        size_t circuit2_idx = coord_in_circuit[pairs[i].coord2_idx];

        if (circuit1_idx == circuit2_idx) {
            continue;
        }

        Circuit *circuit1 = &circuits[circuit1_idx];
        Circuit *circuit2 = &circuits[circuit2_idx];

        for (size_t j = 0; j < circuit2->len; j++) {
            coord_in_circuit[circuit2->coord_idxs[j]] = circuit1_idx;
            circuit1->coord_idxs[circuit1->len++] = circuit2->coord_idxs[j];
        }

        circuit2->len = 0;
    }

    qsort(circuits, circuits_len, sizeof(Circuit), compare_circuit_len_reversed);

    long answer_p1 = circuits[0].len * circuits[1].len * circuits[2].len;

    printf("--- Day 8: Playground ---\n");
    printf("Answer for part 1: %ld\n", answer_p1);

    free(pairs);
    free(circuits);
}
