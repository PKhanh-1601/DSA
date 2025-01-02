//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 7
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;

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
    void findBridgesUtil(int node, int parent, map<int, bool>& visited, map<int, int>& discovery, map<int, int>& low, int& time, vector<pair<int, int> >& bridges)
    {
        visited[node] = true;
        discovery[node] = low[node] = ++time;
        for (int neighbor : adjList[node])
        {
            if (!visited[neighbor])
            {
                findBridgesUtil(neighbor, node, visited, discovery, low, time, bridges);
                low[node] = min(low[node], low[neighbor]);
                if (low[neighbor] > discovery[node])
                {
                    bridges.push_back({node, neighbor});
                }
            }
            else if (neighbor != parent)
            {
                low[node] = min(low[node], discovery[neighbor]);
            }
        }
    }
    vector<pair<int, int> > findBridges()
    {
        map<int, bool> visited;
        map<int, int> discovery;
        map<int, int> low;
        vector<pair<int, int> > bridges;
        int time = 0;
        for (const auto& pair : adjList)
        {
            int node = pair.first;
            if (!visited[node])
            {
                findBridgesUtil(node, -1, visited, discovery, low, time, bridges);
            }
        }

        return bridges;
    }
};

int main()
{
    Graph graph;
    graph.inputGraph();
    vector<pair<int, int>> bridges = graph.findBridges();
    cout << "The bridges in the graph are:\n";
    for (const auto& bridge : bridges)
    {
        cout << bridge.first << " - " << bridge.second << endl;
    }

    return 0;
}
