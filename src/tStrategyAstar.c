#include "tStrategyAstar.h"
#include "tPriorityQueue.h"
#include "tPointHash.h"
#include "tStrategy.h"

typedef struct {
    int g_cost;
    int parent_x;
    int parent_y;
    int closed;
} AuxInfo;


struct solution {
    int total_moves;
    Point** path;
};


AuxInfo** createAuxGridAstar(int rows, int cols) {
    AuxInfo** info = (AuxInfo**)malloc(rows * sizeof(AuxInfo*));
    for (int i = 0; i < rows; i++) {
        info[i] = (AuxInfo*)malloc(cols * sizeof(AuxInfo));
        for (int j = 0; j < cols; j++) {
            info[i][j].g_cost = INT_MAX;
            info[i][j].parent_x = -1;
            info[i][j].parent_y = -1;
            info[i][j].closed = 0;
        }
    }
    return info;
}

void freeAuxGridAstar(AuxInfo** info, int rows) {
    for (int i = 0; i < rows; i++) {
        free(info[i]);
    }
    free(info);
}

void reconstructPathAstar(Solution* sol, AuxInfo** info, int target_x, int target_y) {
    int cx = target_x;
    int cy = target_y;
    int idx = getTotalMoves(sol);
    
    while (cx != -1 && cy != -1) {
        setPathAt(sol,idx--,initPoint(cx, cy));
        int px = info[cx][cy].parent_x;
        int py = info[cx][cy].parent_y;
        cx = px;
        cy = py;
    }
}


static int manhattanDistance(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    return (dx + dy) / 3; 
}

Solution* findPathAstar(PointHash* grid, Point* origin, Point* target) {
    if (!grid || !origin || !target) return NULL;

    int rows = getRows(grid);
    int cols = getCols(grid);
    int start_x = getX(origin), start_y = getY(origin);
    int target_x = getX(target), target_y = getY(target);


    if(hasObstacle(grid, target_x, target_y) == 1){
        Solution* sol = initSolution(-1);
        return sol;
    }

    AuxInfo** info = createAuxGridAstar(rows, cols);
    PriorityQueue* pq = initPQ();

    info[start_x][start_y].g_cost = 0;
    int start_h = manhattanDistance(start_x, start_y, target_x, target_y);
    enqueuePQ(pq, start_x, start_y, start_h); // f = g(0) + h

    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    int reached_target = 0;


    while (!isPQEmpty(pq)) {
        PQNode* curr = dequeuePQ(pq);
        int cx = getNodeXPQ(curr);
        int cy = getNodeYPQ(curr);
        free(curr);


        if (info[cx][cy].closed) continue;

        info[cx][cy].closed = 1;

        if (cx == target_x && cy == target_y) {
            reached_target = 1;
            break;
        }

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (hasObstacle(grid, nx, ny) != 1 && !info[nx][ny].closed) {
                    
                    int tentative_g = info[cx][cy].g_cost + 1;
                    if (tentative_g < info[nx][ny].g_cost) {
                        info[nx][ny].g_cost = tentative_g;
                        info[nx][ny].parent_x = cx;
                        info[nx][ny].parent_y = cy;

                        // f_cost = g_cost + h_cost
                        int h = manhattanDistance(nx, ny, target_x, target_y);
                        int f = tentative_g + h;
                        
                        enqueuePQ(pq, nx, ny, f);
                    }
                }
            }
        }
    }
    
    Solution* sol;
    if (reached_target) {
        sol = initSolution(info[target_x][target_y].g_cost);
        reconstructPathAstar(sol, info, target_x, target_y);
    } else {
        sol = initSolution(-1);
    }

    freePQ(pq);
    freeAuxGridAstar(info, rows);
    return sol;
}

void freeAstarStrategy(Strategy* s){
    free(s);
}

Strategy* createStrategyAstar() {
    Strategy* s = malloc(sizeof(Strategy));
    s->findPath = findPathAstar;
    s->freeStrategy = freeAstarStrategy;
    return s;
}