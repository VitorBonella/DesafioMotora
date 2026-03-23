#ifndef MOTORACHALLENGE_SOLVER_H
#define MOTORACHALLENGE_SOLVER_H

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "tPointHash.h"
#include "tPriorityQueue.h"

typedef struct solver Solver;
typedef struct solution Solution;

Solver* initSolver(const char* filename);

Solution* findPath(Solver* s);
void printSolution(Solution* sol);
void freeSolver(Solver* s);
void freeSolution(Solution* sol);

#endif