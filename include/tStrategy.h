#ifndef MOTORACHALLENGE_STRATEGY_H
#define MOTORACHALLENGE_STRATEGY_H

#include "tPointHash.h"
#include "tSolution.h"

//iface
typedef struct strategy {
    Solution* (*findPath)(PointHash* grid, Point* origin, Point* target);
    void (*freeStrategy)(struct strategy* s);
} Strategy;

#endif