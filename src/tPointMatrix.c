#include "tPointMatrix.h"

struct pointMatrix {
    int rows;
    int cols;
    Point*** grid;
};

PointMatrix* initMatrix(int rows, int cols) {
    PointMatrix* m = (PointMatrix*)malloc(sizeof(PointMatrix));
    if (m == NULL) return NULL;

    m->rows = rows;
    m->cols = cols;

    m->grid = (Point***)malloc(rows * sizeof(Point**));
    
    for (int i = 0; i < rows; i++) {
        m->grid[i] = (Point**)malloc(cols * sizeof(Point*));
        for (int j = 0; j < cols; j++) {
            m->grid[i][j] = initPoint(i, j); 
        }
    }

    return m;
}

void setObstacle(PointMatrix* m, int x, int y) {
    if (m == NULL || x < 0 || x >= m->rows || y < 0 || y >= m->cols) {
        return;
    }

    if (m->grid[x][y] != NULL) {
       setIsObstacle(m->grid[x][y]);
    }
}

void freePointMatrix(PointMatrix* m) {
    if (m == NULL) return;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            if (m->grid[i][j] != NULL) {
                freePoint(m->grid[i][j]); 
            }
        }
        free(m->grid[i]);
    }
    free(m->grid);
    free(m);
}

int getRows(PointMatrix* m){
    if(m == NULL) return -1;
    return m->rows;
}

int getCols(PointMatrix* m){
    if(m == NULL) return -1;
    return m->cols;
}

int hasObstacle(PointMatrix* m, int x, int y) {
    if (m == NULL || m->grid == NULL) {
        printf("error");
        return -1; 
    }

    if (x < 0 || x >= m->rows || y < 0 || y >= m->cols) {
        return -1;
    }

    Point* targetPoint = m->grid[x][y];

    if (targetPoint == NULL) {
        printf("error");
        return 0;
    }

    return getIsObstacle(targetPoint);
}