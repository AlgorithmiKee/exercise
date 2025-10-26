#include <iostream>
#include <vector>
#include <array>
#include <queue>

using namespace std;

using Maze = vector<vector<char>>;
using Point = array<int, 2>;

/**
 * Maze:
 * '.': not yet visited
 * 'v': visited
 * '*': wall
 */

bool withinBoundary(int x, int y, int nrows, int ncols) {
    if(x < 0 || x >= nrows || y < 0 || y >= ncols) {
        return false;
    }
    return true;
}

bool solveMaze(Maze& grid) {
    int nrows = grid.size();
    int ncols = grid[0].size();
    vector<int> dx = {-1, 1, 0, 0};
    vector<int> dy = {0, 0, -1, 1};

    Point start = {-1, -1};
    Point exit = {-1, -1};

    // locate the starting point and the exit
    bool locatedStart = false;
    bool locatedExit = false;
    for(int i = 0; i < nrows; i++) {
        for(int j = 0; j < ncols; j++) {
            if(grid[i][j] == 'S') {
                start = {i,j};
                locatedStart = true;
            }
            if(grid[i][j] == 'E') {
                exit = {i,j};
                locatedExit = true;
            }
            if(locatedStart && locatedExit) {
                break;
            }
        }
    }

    // defence against ill grid
    if(start == Point{-1,-1} || exit == Point{-1,-1}) {
        cout << "Missing start or exit in the grid" << endl;
        return false;
    }

    // BFS
    queue<Point> q;
    q.push(start);
    grid[start[0]][start[1]] = 'v';

    while(!q.empty()) {
        auto p = q.front();
        q.pop();

        if(p == exit) {
            return true;
        }

        int x = p[0];
        int y = p[1];

        // enqueue unvisited neighbours
        for(int i = 0; i < 4; i++) {
            int nextX = x + dx[i];
            int nextY = y + dy[i];
            if(!withinBoundary(nextX, nextY, nrows, ncols)) {
                continue;
            }
            if(grid[nextX][nextY] == 'v' || grid[nextX][nextY] == '*') {
                continue;
            }
            grid[nextX][nextY] = 'v';
            q.push(Point{nextX, nextY});
        }
    }
    return false;
}

void printMaze(const Maze& grid) {
    for(auto row : grid) {
        for(auto elem : row) {
            cout << elem << " ";
        }
        cout << endl;
    }
}

int main() {
    Maze m = {
        {'S', '.', '.', '*', '.', '*'},
        {'.', '*', '.', '*', '*', '.'},
        {'.', '*', '.', '*', '*', '.'},
        {'*', '.', '*', '.', '.', '.'},
        {'.', '.', '*', '.', '*', '.'},
        {'.', '.', '.', '.', '*', 'E'},
    };
    
    printMaze(m);

    int nrows = m.size();
    int ncols = m[0].size();
    Point start = {0,0};
    Point exit = {nrows-1, ncols-1};

    if(solveMaze(m)) {
        cout << "Path Exist" << endl;
    }
    else {
        cout << "No Path" << endl;
    }

    printMaze(m);

    return 0;
}