#include "tPointHash.h"

#define HASH_CAPACITY 10007 

typedef struct hashNode {
    Point* point;
    struct hashNode* next;
} HashNode;


struct pointHash {
    int rows;
    int cols;
    int capacity;
    HashNode** table; 
};


static int hashFunction(int x, int y, int capacity) {
    unsigned int hash = (x * 857743) + y;
    return hash % capacity;
}


PointHash* initHashTable(int rows, int cols) {

    PointHash* m = (PointHash*) malloc(sizeof(PointHash));
    if (m == NULL) return NULL;

    m->rows = rows;
    m->cols = cols;
    m->capacity = HASH_CAPACITY;

    m->table = (HashNode**) calloc(m->capacity, sizeof(HashNode*));
    if (m->table == NULL) {
        free(m);
        return NULL;
    }

    return m;
}

int getRows(PointHash* m){
    return m? m->rows : -1;
}
int getCols(PointHash* m){
    return m? m->cols : -1;
}

void setObstacle(PointHash* m, int x, int y) {
    if (m == NULL || x < 0 || x >= m->rows || y < 0 || y >= m->cols) {
        return;
    }

    int index = hashFunction(x, y, m->capacity);

    HashNode* current = m->table[index];
    while (current != NULL) {
        if (getX(current->point) == x && getY(current->point) == y) {
            setIsObstacle(current->point); 
            return;
        }
        current = current->next;
    }


    Point* p = initPoint(x, y);
    setIsObstacle(p);


    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (newNode == NULL) return;
    
    newNode->point = p;
    newNode->next = m->table[index]; 
    m->table[index] = newNode;
}


int hasObstacle(PointHash* m, int x, int y) {
    if (m == NULL || x < 0 || x >= m->rows || y < 0 || y >= m->cols) {
        return -1;
    }

    int index = hashFunction(x, y, m->capacity);
    HashNode* current = m->table[index];

    while (current != NULL) {
        if (getX(current->point) == x && getY(current->point) == y) {
            return getIsObstacle(current->point);
        }
        current = current->next;
    }

    return 0; 
}

void freePointMatrix(PointHash* m) {
    if (m == NULL) return;

    for (int i = 0; i < m->capacity; i++) {
        HashNode* current = m->table[i];
        
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            freePoint(temp->point);
            free(temp);
        }
    }
    
    free(m->table);
    free(m);
}