#include "tSolver.h"

struct solver{
    PointMatrix* grid;
    Point* origin;
    Point* target;
};

static void parse_dimensions(FILE* file, int* r, int* c) {
    if (fscanf(file, "%d %d", r, c) != 2) {
        *r = 0; *c = 0;
    }
}

static Point* parse_point(FILE* file) {
    int x, y;
    if (fscanf(file, "%d %d", &x, &y) == 2) {
        return initPoint(x, y);
    }
    return NULL;
}

static void parse_obstacles(FILE* file, PointMatrix* grid) {
    int numObstacles, obsX, obsY;
    if (fscanf(file, "%d", &numObstacles) == 1) {
        for (int i = 0; i < numObstacles; i++) {
            if (fscanf(file, "%d %d", &obsX, &obsY) == 2) {
                setObstacle(grid, obsX, obsY);
            }
        }
    }
}

Solver* initSolver(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    Solver* s = (Solver*)malloc(sizeof(Solver));
    if (!s) {
        fclose(file);
        return NULL;
    }

    int rows, cols;
    parse_dimensions(file, &rows, &cols);
    s->grid = initMatrix(rows, cols);

    s->origin = parse_point(file);
    s->target = parse_point(file);

    parse_obstacles(file, s->grid);

    fclose(file);
    return s;
}

void freeSolver(Solver* s){

    freePointMatrix(s->grid);
    freePoint(s->origin);
    freePoint(s->target);
    free(s);

}

struct solution {
    int total_moves;
    Point** path;
};

typedef struct {
    int visited; // 0 false | 1 tru
    int dist;
    int parent_x;
    int parent_y;
} AuxInfo;

AuxInfo** createAuxGrid(int rows, int cols) {
    AuxInfo** info = (AuxInfo**)malloc(rows * sizeof(AuxInfo*));
    for (int i = 0; i < rows; i++) {
        info[i] = (AuxInfo*)calloc(cols, sizeof(AuxInfo));
    }
    return info;
}

void freeAuxGrid(AuxInfo** info, int rows) {
    for (int i = 0; i < rows; i++) {
        free(info[i]);
    }
    free(info);
}

void reconstructPath(Solution* sol, AuxInfo** info, int target_x, int target_y) {
    sol->total_moves = info[target_x][target_y].dist;
    sol->path = (Point**)malloc((sol->total_moves + 1) * sizeof(Point*));
    
    int cx = target_x;
    int cy = target_y;
    int idx = sol->total_moves;
    
    while (cx != -1 && cy != -1) {
        sol->path[idx--] = initPoint(cx, cy);
        int px = info[cx][cy].parent_x;
        int py = info[cx][cy].parent_y;
        cx = px;
        cy = py;
    }
}

Solution* findPath(Solver* s) {
    if (!s || !s->grid || !s->origin || !s->target) return NULL;

    int rows = getRows(s->grid);
    int cols = getCols(s->grid);
    int start_x = getX(s->origin), start_y = getY(s->origin);
    int target_x = getX(s->target), target_y = getY(s->target);

    AuxInfo** info = createAuxGrid(rows, cols);
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
                if (!info[nx][ny].visited && !hasObstacle(s->grid, nx, ny)) {
                    info[nx][ny].visited = 1;
                    info[nx][ny].dist = info[cx][cy].dist + 1;
                    info[nx][ny].parent_x = cx;
                    info[nx][ny].parent_y = cy;
                    enqueue(q, nx, ny);
                }
            }
        }
    }


    Solution* sol = (Solution*)malloc(sizeof(Solution));
    if (reached_target) {
        reconstructPath(sol, info, target_x, target_y);
    } else {
        sol->total_moves = -1;
        sol->path = NULL;
    }

    freeQueue(q);
    freeAuxGrid(info, rows);
    return sol;
}

void printSolution(Solution* sol){
    if (!sol) return;

    if (sol->total_moves == -1) {
        printf("-1\n");
    } else {
        printf("Total Moves: %d\n", sol->total_moves);
        
        for (int i = 0; i <= sol->total_moves; i++) {
            printf("(%d, %d)\n", getX(sol->path[i]), getY(sol->path[i]));
        }
    }
}

void freeSolution(Solution* sol){
    for(int i = 0;i < (sol->total_moves + 1); i++){
        freePoint(sol->path[i]);
    }
    free(sol->path);
    free(sol);
}