#include "tSolver.h"
#include "tStrategyBFS.h"
#include "tStrategyAstar.h"
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <file> <bfs|astar>\n", argv[0]);
        return 1;
    }

    Strategy* selectedStrategy = NULL;

    if (strcmp(argv[2], "bfs") == 0) {
        selectedStrategy = createStrategyBFS();
    } else {
        selectedStrategy = createStrategyAstar();
    }

    Solver* s = initSolver(argv[1], selectedStrategy);
    Solution* sol = findPath(s);

    printSolution(sol);

    freeSolution(sol);

    freeSolver(s);
    
    return 0;
}