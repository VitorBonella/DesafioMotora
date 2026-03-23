#include "tSolver.h"
#include <stdlib.h>

struct solver {
    PointHash* grid;
    Point* origin;
    Point* target;
    Strategy* strategy;
};

static void parse_dimensions(FILE* file, int* r, int* c) {
    if (fscanf(file, "%d %d", r, c) != 2) {
        *r = 0; *c = 0;
    }
}

static Point* parse_point(FILE* file) {
    int x, y;
    if (fscanf(file, "%d %d", &x, &y) == 2) {
        return initPoint(x, y);
    }
    return NULL;
}

static void parse_obstacles(FILE* file, PointHash* grid) {
    int numObstacles, obsX, obsY;
    if (fscanf(file, "%d", &numObstacles) == 1) {
        for (int i = 0; i < numObstacles; i++) {
            if (fscanf(file, "%d %d", &obsX, &obsY) == 2) {
                setObstacle(grid, obsX, obsY);
            }
        }
    }
}

Solver* initSolver(const char* filename, Strategy* strategy) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    Solver* s = malloc(sizeof(Solver));
    int r, c;
    parse_dimensions(file, &r, &c);
    s->grid = initHashTable(r, c);
    s->origin = parse_point(file);
    s->target = parse_point(file);
    parse_obstacles(file, s->grid);
    s->strategy = strategy;

    fclose(file);
    return s;
}

Solution* findPath(Solver* s) {
    return s->strategy->findPath(s->grid, s->origin, s->target);
}

void freeSolver(Solver* s) {
    freePointMatrix(s->grid);
    freePoint(s->origin);
    freePoint(s->target);
    if (s->strategy->freeStrategy) s->strategy->freeStrategy(s->strategy);
    free(s);
}
