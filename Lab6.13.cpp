//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 13
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <climits>
using namespace std;

struct Edge
{
    int target;
    int weight;
};

class Graph
{
public:
    unordered_map<int, vector<Edge>> adjList;

    void addEdge(int source, int target, int weight)
    {
        adjList[source].push_back({target, weight});
        adjList[target].push_back({source, weight});
    }
};

vector<int> dijkstra(Graph& graph, int start, int target)
{
    unordered_map<int, int> dist;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    for (const auto& node : graph.adjList)
    {
        dist[node.first] = INT_MAX;
    }

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int current = pq.top().second;
        int currentDist = pq.top().first;
        pq.pop();

        if (current == target) break;

        for (const auto& edge : graph.adjList[current])
        {
            int neighbor = edge.target;
            int weight = edge.weight;

            if (currentDist + weight < dist[neighbor])
            {
                dist[neighbor] = currentDist + weight;
                parent[neighbor] = current;
                pq.push({dist[neighbor], neighbor});
            }
        }
    }

    vector<int> path;
    int trace = target;
    if (dist[trace] == INT_MAX) return {};
    while (trace != start)
    {
        path.push_back(trace);
        trace = parent[trace];
    }
    path.push_back(start);
    reverse(path.begin(), path.end());

    return path;
}

int main() {
    Graph city;

    city.addEdge(1, 2, 5);
    city.addEdge(1, 3, 2);
    city.addEdge(2, 3, 10);
    city.addEdge(2, 4, 8);
    city.addEdge(3, 4, 3);

    int start = 1, target = 4;

    cout << "Finding shortest path from " << start << " to " << target << "...\n";
    vector<int> path = dijkstra(city, start, target);

    if (!path.empty())
    {
        cout << "Path found: ";
        for (int node : path)
        {
            cout << node << " ";
        }
        cout << endl;
    }
    else
    {
        cout << "No path exists.\n";
    }
    return 0;
}

