#ifndef MOTORACHALLENGE_PRIORITYQUEUE_H
#define MOTORACHALLENGE_PRIORITYQUEUE_H

#include <stdio.h>
#include <stdlib.h>

typedef struct priorityQueue PriorityQueue;
typedef struct pqNode PQNode;

PriorityQueue* initPQ();
void enqueuePQ(PriorityQueue* pq, int x, int y, int f_cost);
PQNode* dequeuePQ(PriorityQueue* pq);
int isPQEmpty(PriorityQueue* pq);
void freePQ(PriorityQueue* pq);

int getNodeX(PQNode* q);
int getNodeY(PQNode* q);
int getNodeFCost(PQNode* q);

#endif