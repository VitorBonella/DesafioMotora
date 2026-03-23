#ifndef MOTORACHALLENGE_POINT_H
#define MOTORACHALLENGE_POINT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct point Point;

Point* initPoint(int x, int y);
int getX(Point* p);
int getY(Point* p);
int getIsObstacle(Point* p);
void setIsObstacle(Point* p);
void freePoint(Point* p);


#endif