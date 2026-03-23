#include "tQueue.h"

struct qNode {
    int x;
    int y;
    struct qNode* next;
};

struct queue {
    QNode* front;
    QNode* rear;
};

Queue* initQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue* q, int x, int y) {
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    newNode->x = x;
    newNode->y = y;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

QNode* dequeue(Queue* q) {
    if (q->front == NULL) return NULL;
    
    QNode* temp = q->front;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    return temp;
}

int isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

int getNodeX(QNode* q){
    if(q == NULL) return -1;
    return q->x;
}

int getNodeY(QNode* q){
    if(q == NULL) return -1;
    return q->y;
}

void freeQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
       QNode* temp = dequeue(q);
       free(temp);
    }
    free(q);
}