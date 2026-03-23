#include "tSolver.h"
#include "tPriorityQueue.h"
#include "tPointHash.h"


struct solver {
    PointHash* grid; 
    Point* origin;
    Point* target;
    int rows;
    int cols;
};

// Estrutura atualizada para suportar o A*
typedef struct {
    int g_cost;
    int parent_x;
    int parent_y;
    int closed;
} AuxInfo;

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

// Atualizado para receber PointHash
static void parse_obstacles(FILE* file, PointHash* grid) {
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

    parse_dimensions(file, &s->rows, &s->cols);
    s->grid = initMatrix(s->rows, s->cols);

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


AuxInfo** createAuxGrid(int rows, int cols) {
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

void freeAuxGrid(AuxInfo** info, int rows) {
    for (int i = 0; i < rows; i++) {
        free(info[i]);
    }
    free(info);
}

void reconstructPath(Solution* sol, AuxInfo** info, int target_x, int target_y) {
    sol->total_moves = info[target_x][target_y].g_cost;
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


static int manhattanDistance(int x1, int y1, int x2, int y2) {
    int dx = abs(x1 - x2);
    int dy = abs(y1 - y2);
    return (dx + dy) / 3; 
}

Solution* findPath(Solver* s) {
    if (!s || !s->grid || !s->origin || !s->target) return NULL;

    int rows = s->rows;
    int cols = s->cols;
    int start_x = getX(s->origin), start_y = getY(s->origin);
    int target_x = getX(s->target), target_y = getY(s->target);

    Solution* sol = (Solution*)malloc(sizeof(Solution));

    if(hasObstacle(s->grid, target_x, target_y) == 1){
        sol->total_moves = -1;
        sol->path = NULL;
        return sol;
    }

    AuxInfo** info = createAuxGrid(rows, cols);
    PriorityQueue* pq = initPQ();

    info[start_x][start_y].g_cost = 0;
    int start_h = calculateHeuristic(start_x, start_y, target_x, target_y);
    enqueuePQ(pq, start_x, start_y, start_h); // f = g(0) + h

    int dx[] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dy[] = {1, -1, 1, -1, 2, -2, 2, -2};
    int reached_target = 0;


    while (!isPQEmpty(pq)) {
        PQNode* curr = dequeuePQ(pq);
        int cx = getNodeX(curr);
        int cy = getNodeY(curr);
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
                if (hasObstacle(s->grid, nx, ny) != 1 && !info[nx][ny].closed) {
                    
                    int tentative_g = info[cx][cy].g_cost + 1;
                    if (tentative_g < info[nx][ny].g_cost) {
                        info[nx][ny].g_cost = tentative_g;
                        info[nx][ny].parent_x = cx;
                        info[nx][ny].parent_y = cy;

                        // f_cost = g_cost + h_cost
                        int h = calculateHeuristic(nx, ny, target_x, target_y);
                        int f = tentative_g + h;
                        
                        enqueuePQ(pq, nx, ny, f);
                    }
                }
            }
        }
    }

    if (reached_target) {
        reconstructPath(sol, info, target_x, target_y);
    } else {
        sol->total_moves = -1;
        sol->path = NULL;
    }

    freePQ(pq);
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
    if(sol && sol->path){
        for(int i = 0; i < (sol->total_moves + 1); i++){
            freePoint(sol->path[i]);
        }
        free(sol->path);
    }
    if(sol) free(sol);
}