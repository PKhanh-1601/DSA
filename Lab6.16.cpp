//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 16
//Notes or Remarks:

#include <iostream>
#include <queue>
#include <cmath>
#include <cstring>
using namespace std;

const int MAX_GRID_SIZE = 100;
const int INF = 1e9;

const int dx[4] = {-1, 1, 0, 0};
const int dy[4] = {0, 0, -1, 1};

struct Node
{
    int x, y;
    int g, h;
    Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h) {}
    int f() const { return g + h; }
    bool operator<(const Node& other) const {
        return f() > other.f();
    }
};

int heuristic(int x1, int y1, int x2, int y2)
{
    return abs(x1 - x2) + abs(y1 - y2);
}

bool aStar(int grid[MAX_GRID_SIZE][MAX_GRID_SIZE], int rows, int cols,
           int startX, int startY, int goalX, int goalY)
{
    bool visited[MAX_GRID_SIZE][MAX_GRID_SIZE];
    memset(visited, false, sizeof(visited));

    priority_queue<Node> pq;
    pq.push(Node(startX, startY, 0, heuristic(startX, startY, goalX, goalY)));

    int parent[MAX_GRID_SIZE][MAX_GRID_SIZE][2];
    memset(parent, -1, sizeof(parent));

    while (!pq.empty())
    {
        Node current = pq.top();
        pq.pop();

        if (current.x == goalX && current.y == goalY)
        {
            // Reconstruct path
            cout << "Path found:\n";
            int x = goalX, y = goalY;
            while (x != -1 && y != -1)
            {
                cout << "(" << x << ", " << y << ") ";
                int tempX = parent[x][y][0];
                int tempY = parent[x][y][1];
                x = tempX;
                y = tempY;
            }
            cout << endl;
            return true;
        }
        if (visited[current.x][current.y]) continue;
        visited[current.x][current.y] = true;

        for (int i = 0; i < 4; ++i)
        {
            int nx = current.x + dx[i];
            int ny = current.y + dy[i];

            if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && !visited[nx][ny] &&
                grid[nx][ny] == 0)
            {
                int g = current.g + 1;
                int h = heuristic(nx, ny, goalX, goalY);
                pq.push(Node(nx, ny, g, h));
                parent[nx][ny][0] = current.x;
                parent[nx][ny][1] = current.y;
            }
        }
    }
    cout << "No path found!" << endl;
    return false;
}

int main()
{
    int rows, cols;
    cout << "Enter grid size (rows and cols): ";
    cin >> rows >> cols;

    int grid[MAX_GRID_SIZE][MAX_GRID_SIZE];
    cout << "Enter the grid (0 for free cell, 1 for obstacle):\n";
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            cin >> grid[i][j];
        }
    }
    int startX, startY, goalX, goalY;
    cout << "Enter start position (x y): ";
    cin >> startX >> startY;
    cout << "Enter goal position (x y): ";
    cin >> goalX >> goalY;
    if (!aStar(grid, rows, cols, startX, startY, goalX, goalY))
    {
        cout << "The NPC could not find a path to the goal." << endl;
    }

    return 0;
}

