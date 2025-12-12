#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TILES 512

typedef struct {
    int x;
    int y;
} Tile;

long calc_area(Tile t1, Tile t2) {
    long w = abs(t1.x - t2.x) + 1;
    long h = abs(t1.y - t2.y) + 1;
    return w * h;
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

    Tile tiles[MAX_TILES];
    size_t tiles_len = 0;

    int x, y;
    while(fscanf(f, "%d,%d", &x, &y) == 2) {
        tiles[tiles_len++] = (Tile){x, y};
    } 

    fclose(f);

    /*
     * TODO: Find a more efficient solution than checking all
     * possible areas!
     */
    long max_area = 0;
    for (size_t i = 0; i < tiles_len - 1; i++) {
        for (size_t j = i + 1; j < tiles_len; j++) {
            long area = calc_area(tiles[i], tiles[j]);
            if (area > max_area) {
                max_area = area;
            }
        }
    }

    printf("--- Day 9: Movie Theater ---\n");
    printf("Answer for part 1: %ld\n", max_area);
}
