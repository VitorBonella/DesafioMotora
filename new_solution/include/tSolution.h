#ifndef MOTORACHALLENGE_SOLUTION_H
#define MOTORACHALLENGE_SOLUTION_H

#include <stdio.h>
#include "tPoint.h"

typedef struct solution Solution;

Solution* initSolution(int total_moves);
void freeSolution(Solution* sol);

void setPathAt(Solution* sol, int index, Point* p);
int getTotalMoves(Solution* sol);
Point* getPathAt(Solution* sol, int index);

void printSolution(Solution* sol);

#endif