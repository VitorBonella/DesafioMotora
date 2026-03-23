#include <stdio.h>
#include "tSolver.h"

int main(int argc, char *argv[]) {
    
    if (argc < 2) {
        printf("Erro: Use %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    Solver* s = initSolver(argv[1]);
 
    Solution* sol = findPath(s);
    
    printSolution(sol);

    freeSolver(s);
    freeSolution(sol);

    return 0;
}
