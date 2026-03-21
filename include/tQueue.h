#ifndef MOTORACHALLENGE_QUEUE_H
#define MOTORACHALLENGE_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "tPoint.h"

typedef struct queue Queue;
typedef struct qNode QNode;

Queue* initQueue();
void enqueue(Queue *q, int x, int y);
QNode* dequeue(Queue* q);
int isQueueEmpty(Queue* q);
void freeQueue(Queue* q);
int getNodeX(QNode* q);
int getNodeY(QNode* q);

#endif