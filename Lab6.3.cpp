//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 3
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph
{
private:
    vector<vector<int> > adjacencyList;
    int numVertices;

public:
    Graph(int vertices) : numVertices(vertices)
    {
        adjacencyList.resize(vertices);
    }
    void addEdge(int u, int v)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Error: Vertex out of range.\n";
            return;
        }
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
    }
    vector<int> bfs(int start)
    {
        vector<int> traversalOrder;
        vector<bool> visited(numVertices, false);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        while (!q.empty())
        {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(current);
            for (size_t i = 0; i < adjacencyList[current].size(); i++)
            {
                int neighbor = adjacencyList[current][i];
                if (!visited[neighbor])
                {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        return traversalOrder;
    }
};

int main()
{
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    Graph graph(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;
    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        graph.addEdge(u, v);
    }

    int startVertex;
    cout << "Enter the starting vertex for BFS: ";
    cin >> startVertex;

    vector<int> traversal = graph.bfs(startVertex);
    cout << "BFS Traversal Order: ";
    for (int node : traversal)
    {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}

