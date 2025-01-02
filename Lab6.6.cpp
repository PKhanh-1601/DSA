//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 6
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct Edge
{
    int target;
    int weight;
};

class Graph
{
public:
    map<int, vector<int> > adjList;

    void addEdge(int source, int target)
    {
        adjList[source].push_back(target);
        adjList[target].push_back(source);
    }

    void inputGraph()
    {
        int numEdges;
        cout << "Enter the number of edges: ";
        cin >> numEdges;
        cout << "Enter each edge in the format (source target):\n";

        for (int i = 0; i < numEdges; ++i)
        {
            int source, target;
            cin >> source >> target;
            addEdge(source, target);
        }
    }

    void DFS(int node, set<int>& visited, vector<int>& component)
    {
        visited.insert(node);
        component.push_back(node);

        for (int neighbor : adjList[node])
        {
            if (visited.find(neighbor) == visited.end())
            {
                DFS(neighbor, visited, component);
            }
        }
    }
    vector<vector<int> > findConnectedComponents()
    {
        set<int> visited;
        vector<vector<int> > components;

        for (const auto& pair : adjList)
        {
            int node = pair.first;
            if (visited.find(node) == visited.end())
            {
                vector<int> component;
                DFS(node, visited, component);
                components.push_back(component);
            }
        }
        return components;
    }
};

int main()
{
    Graph graph;
    graph.inputGraph();

    vector<vector<int>> components = graph.findConnectedComponents();

    cout << "The connected components of the graph are:\n";
    for (const auto& component : components)
    {
        for (int node : component)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    return 0;
}

