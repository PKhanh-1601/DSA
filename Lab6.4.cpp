//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 4
//Notes or Remarks:

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    int numVertices;
    vector<vector<int> > adjacencyList;

    bool dfsCycleDirected(int vertex, vector<bool> &visited, vector<bool> &recStack)
    {
        visited[vertex] = true;
        recStack[vertex] = true;

        for (int neighbor : adjacencyList[vertex])
        {
            if (!visited[neighbor])
            {
                if (dfsCycleDirected(neighbor, visited, recStack))
                {
                    return true;
                }
            }
        else if (recStack[neighbor])
            {
                return true;
            }
        }
        recStack[vertex] = false;
        return false;
    }

    bool dfsCycleUndirected(int vertex, vector<bool> &visited, int parent)
    {
        visited[vertex] = true;
        for (int neighbor : adjacencyList[vertex])
        {
            if (!visited[neighbor])
            {
                if (dfsCycleUndirected(neighbor, visited, vertex))
                {
                    return true;
                }
            }
        else if (neighbor != parent)
            {
                return true;
            }
        }
        return false;
    }

public:
    Graph(int vertices) : numVertices(vertices)
    {
        adjacencyList.resize(vertices);
    }
    void addEdge(int u, int v, bool isDirected)
    {
        adjacencyList[u].push_back(v);
        if (!isDirected)
        {
            adjacencyList[v].push_back(u);
        }
    }

    bool detectCycleDirected()
    {
        vector<bool> visited(numVertices, false);
        vector<bool> recStack(numVertices, false);

        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                if (dfsCycleDirected(i, visited, recStack))
                {
                    return true;
                }
            }
        }
        return false;
    }

    bool detectCycleUndirected()
    {
        vector<bool> visited(numVertices, false);

        for (int i = 0; i < numVertices; i++)
        {
            if (!visited[i])
            {
                if (dfsCycleUndirected(i, visited, -1))
                {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    Graph directedGraph(vertices);
    Graph undirectedGraph(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges for a directed graph (u v):\n";
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        directedGraph.addEdge(u, v, true);
    }

    cout << "Enter the edges for an undirected graph (u v):\n";
    for (int i = 0; i < edges; i++)
    {
        int u, v;
        cin >> u >> v;
        undirectedGraph.addEdge(u, v, false);
    }

    if (directedGraph.detectCycleDirected())
    {
        cout << "Cycle detected in the directed graph.\n";
    }
    else
    {
        cout << "No cycle detected in the directed graph.\n";
    }
    if (undirectedGraph.detectCycleUndirected())
    {
        cout << "Cycle detected in the undirected graph.\n";
    }
    else
    {
        cout << "No cycle detected in the undirected graph.\n";
    }

    return 0;
}

