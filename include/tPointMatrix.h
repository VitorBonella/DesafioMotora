#ifndef MOTORACHALLENGE_MATRIX_H
#define MOTORACHALLENGE_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include "tPoint.h"

typedef struct pointMatrix PointMatrix;

PointMatrix* initMatrix(int rows, int cols);
void setObstacle(PointMatrix* m, int x, int y);
void freePointMatrix(PointMatrix* m);
int getRows(PointMatrix* m);
int getCols(PointMatrix* m);
int hasObstacle(PointMatrix* m, int x, int y);

#endif