#include "tPoint.h"

struct point{
    int x;
    int y;
    int isObstacle; //0 false | 1 true
};

Point* initPoint(int x, int y){
    Point* p = (Point*) malloc(sizeof(Point));

    if(p != NULL){
        p->x = x;
        p->y = y;
        p->isObstacle = 0;
    }

    return p;
}

int getX(Point* p){
    if(p == NULL) return -1;
    return p->x;
}

int getY(Point* p){
    if(p == NULL) return -1;
    return p->y;
}

void setIsObstacle(Point* p){
    if(p == NULL) return;

    p->isObstacle = 1;
}

int getIsObstacle(Point* p){
    if(p == NULL) return -1;

    return p->isObstacle;
}

void freePoint(Point* p){
    free(p);
}