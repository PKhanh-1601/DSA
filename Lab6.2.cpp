//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 2
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <stack>
#include <cstring>
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
    void dfsRecursiveHelper(int vertex, vector<bool> &visited)
    {
        visited[vertex] = true;
        cout << vertex << " ";
        for (size_t i = 0; i < adjacencyList[vertex].size(); i++)
        {
            int neighbor = adjacencyList[vertex][i];
            if (!visited[neighbor])
            {
                dfsRecursiveHelper(neighbor, visited);
            }
        }
    }

    void dfsRecursive(int start)
    {
        vector<bool> visited(numVertices, false);
        cout << "DFS (Recursive): ";
        dfsRecursiveHelper(start, visited);
        cout << endl;
    }

    void dfsIterative(int start)
    {
        vector<bool> visited(numVertices, false);
        stack<int> s;

        s.push(start);
        cout << "DFS (Iterative): ";
        while (!s.empty()) {
            int vertex = s.top();
            s.pop();

            if (!visited[vertex])
            {
                visited[vertex] = true;
                cout << vertex << " ";
                for (int i = adjacencyList[vertex].size() - 1; i >= 0; i--)
                {
                    int neighbor = adjacencyList[vertex][i];
                    if (!visited[neighbor])
                    {
                        s.push(neighbor);
                    }
                }
            }
        }
        cout << endl;
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
    cout << "Enter the starting vertex for DFS: ";
    cin >> startVertex;

    graph.dfsRecursive(startVertex);
    graph.dfsIterative(startVertex);

    return 0;
}
