#include "tStrategyBFS.h"

typedef struct {
    int visited; // 0 false | 1 tru
    int dist;
    int parent_x;
    int parent_y;
} AuxInfo;

AuxInfo** createAuxGridBFS(int rows, int cols) {
    AuxInfo** info = (AuxInfo**)malloc(rows * sizeof(AuxInfo*));
    for (int i = 0; i < rows; i++) {
        info[i] = (AuxInfo*)calloc(cols, sizeof(AuxInfo));
    }
    return info;
}

void freeAuxGridBFS(AuxInfo** info, int rows) {
    for (int i = 0; i < rows; i++) {
        free(info[i]);
    }
    free(info);
}

void reconstructPathBFS(Solution* sol, AuxInfo** info, int target_x, int target_y) {
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


Solution* findPathBFS(PointHash* grid, Point* origin, Point* target) {
    if (!grid || !origin || !target) return NULL;

    int rows = getRows(grid);
    int cols = getCols(grid);
    int start_x = getX(origin), start_y = getY(origin);
    int target_x = getX(target), target_y = getY(target);


    if(hasObstacle(grid, target_x, target_y)){
        Solution* sol = initSolution(-1);
        return sol;
    }

    AuxInfo** info = createAuxGridBFS(rows, cols);
    Queue* q = initQueue();

    enqueue(q, start_x, start_y);
    info[start_x][start_y].visited = 1;
    info[start_x][start_y].dist = 0;
    info[start_x][start_y].parent_x = -1;
    info[start_x][start_y].parent_y = -1;

    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    int reached_target = 0;

    while (!isQueueEmpty(q)) {
        QNode* curr = dequeue(q);
        int cx = getNodeX(curr);
        int cy = getNodeY(curr);
        free(curr);

        if (cx == target_x && cy == target_y) {
            reached_target = 1;
            break;
        }

        for (int i = 0; i < 8; i++) {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
                if (!info[nx][ny].visited && !hasObstacle(grid, nx, ny)) {
                    info[nx][ny].visited = 1;
                    info[nx][ny].dist = info[cx][cy].dist + 1;
                    info[nx][ny].parent_x = cx;
                    info[nx][ny].parent_y = cy;
                    enqueue(q, nx, ny);
                }
            }
        }
    }

    Solution* sol;
    if (reached_target) {
        sol = initSolution(info[target_x][target_y].dist);
        reconstructPathBFS(sol, info, target_x, target_y);
    } else {
        sol = initSolution(-1);
    }

    freeQueue(q);
    freeAuxGridBFS(info, rows);
    return sol;
}

void freeBFSStrategy(Strategy* s){
    free(s);
}

Strategy* createStrategyBFS() {
    Strategy* s = malloc(sizeof(Strategy));
    s->findPath = findPathBFS;
    s->freeStrategy = freeBFSStrategy;
    return s;
}