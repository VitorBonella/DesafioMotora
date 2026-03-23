#ifndef MOTORACHALLENGE_SOLVER_H
#define MOTORACHALLENGE_SOLVER_H

#include "tStrategy.h"

typedef struct solver Solver;

Solver* initSolver(const char* filename, Strategy* strategy);
Solution* findPath(Solver* s);
void freeSolver(Solver* s);

#endif