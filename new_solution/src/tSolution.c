#include "tSolution.h"
#include <stdlib.h>

struct solution {
    int total_moves;
    Point** path;
};

Solution* initSolution(int total_moves) {
    Solution* sol = (Solution*)malloc(sizeof(Solution));
    if (!sol) return NULL;

    sol->total_moves = total_moves;
    if (total_moves == -1) {
        sol->path = NULL;
    } else {
        sol->path = (Point**)malloc((total_moves + 1) * sizeof(Point*));
        for (int i = 0; i <= total_moves; i++) sol->path[i] = NULL;
    }
    return sol;
}


void setPathAt(Solution* sol, int index, Point* p) {
    if (sol && sol->path && index >= 0 && index <= sol->total_moves) {
        sol->path[index] = p;
    }
}


int getTotalMoves(Solution* sol) {
    return sol ? sol->total_moves : -1;
}

Point* getPathAt(Solution* sol, int index) {
    if (sol && sol->path && index >= 0 && index <= sol->total_moves) {
        return sol->path[index];
    }
    return NULL;
}

void printSolution(Solution* sol) {
    if (!sol) return;
    if (sol->total_moves == -1) {
        printf("-1\n");
    } else {
        printf("Total Moves: %d\n", sol->total_moves);
        for (int i = 0; i <= sol->total_moves; i++) {
            Point* p = sol->path[i];
            if (p) {
                printf("(%d, %d)\n", getX(p), getY(p));
            }
        }
    }
}

void freeSolution(Solution* sol) {
    if (!sol) return;
    if (sol->path) {
        for (int i = 0; i <= sol->total_moves; i++) {
            if (sol->path[i]) freePoint(sol->path[i]);
        }
        free(sol->path);
    }
    free(sol);
}