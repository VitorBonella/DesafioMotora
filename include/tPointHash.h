#ifndef MOTORACHALLENGE_POINTHASHTABLE_H
#define MOTORACHALLENGE_POINTHASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include "tPoint.h"

typedef struct pointHash PointHash;

PointHash* initHashTable(int rows, int cols);
void setObstacle(PointHash* m, int x, int y);
void freePointMatrix(PointHash* m);
int hasObstacle(PointHash* m, int x, int y);
int getRows(PointHash* m);
int getCols(PointHash* m);

#endif