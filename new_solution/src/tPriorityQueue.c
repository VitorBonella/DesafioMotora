#include "tPriorityQueue.h"

#define INITIAL_CAPACITY 1024

struct pqNode {
    int x;
    int y;
    int f_cost;
};

struct priorityQueue {
    PQNode** array;
    int capacity;
    int size;
};


PriorityQueue* initPQ() {
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) return NULL;

    pq->capacity = INITIAL_CAPACITY;
    pq->size = 0;
    pq->array = (PQNode**)malloc(pq->capacity * sizeof(PQNode*));
    
    if (!pq->array) {
        free(pq);
        return NULL;
    }

    return pq;
}


int isPQEmpty(PriorityQueue* pq) {
    return (pq == NULL || pq->size == 0);
}


static void swap(PQNode** a, PQNode** b) {
    PQNode* temp = *a;
    *a = *b;
    *b = temp;
}

// Reorganiza a árvore de baixo para cima (quando um item é inserido)
static void heapifyUp(PriorityQueue* pq, int index) {
    if (index == 0) return;

    int parentIndex = (index - 1) / 2;

    if (pq->array[index]->f_cost < pq->array[parentIndex]->f_cost) {
        swap(&pq->array[index], &pq->array[parentIndex]);
        heapifyUp(pq, parentIndex); 
    }
}


static void heapifyDown(PriorityQueue* pq, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < pq->size && pq->array[leftChild]->f_cost < pq->array[smallest]->f_cost) {
        smallest = leftChild;
    }

    if (rightChild < pq->size && pq->array[rightChild]->f_cost < pq->array[smallest]->f_cost) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(&pq->array[index], &pq->array[smallest]);
        heapifyDown(pq, smallest);
    }
}

void enqueuePQ(PriorityQueue* pq, int x, int y, int f_cost) {
    if (!pq) return;

    if (pq->size == pq->capacity) {
        pq->capacity *= 2;
        pq->array = (PQNode**)realloc(pq->array, pq->capacity * sizeof(PQNode*));
    }

    PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
    newNode->x = x;
    newNode->y = y;
    newNode->f_cost = f_cost;

    pq->array[pq->size] = newNode;
    heapifyUp(pq, pq->size);
    pq->size++;
}


PQNode* dequeuePQ(PriorityQueue* pq) {
    if (isPQEmpty(pq)) return NULL;

    PQNode* root = pq->array[0];

    pq->array[0] = pq->array[pq->size - 1];
    pq->size--;

    heapifyDown(pq, 0);

    return root;
}

int getNodeXPQ(PQNode* q) {
    if (q == NULL) return -1;
    return q->x;
}

int getNodeYPQ(PQNode* q) {
    if (q == NULL) return -1;
    return q->y;
}

int getNodeFCost(PQNode* q) {
    if (q == NULL) return -1;
    return q->f_cost;
}


void freePQ(PriorityQueue* pq) {
    if (!pq) return;

    for (int i = 0; i < pq->size; i++) {
        free(pq->array[i]);
    }
    
    free(pq->array);
    free(pq);
}