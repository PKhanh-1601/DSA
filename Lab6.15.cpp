//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 15
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <algorithm>
using namespace std;

const int INF = numeric_limits<int>::max();

struct Edge
{
    int to, weight;
};

void dijkstra(int start, const vector<vector<Edge> >& graph, vector<int>& distances)
{
    int n = graph.size();
    distances.assign(n, INF);
    distances[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<> > pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int curr_dist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();
        if (curr_dist > distances[curr]) continue;
        for (const auto& edge : graph[curr])
        {
            int next = edge.to;
            int weight = edge.weight;

            if (distances[curr] + weight < distances[next])
            {
                distances[next] = distances[curr] + weight;
                pq.push({distances[next], next});
            }
        }
    }
}

void findBridges(int u, int parent, vector<vector<int>>& graph, vector<bool>& visited,
                 vector<int>& discovery, vector<int>& low, vector<pair<int, int>>& bridges, int& time)
{
    visited[u] = true;
    discovery[u] = low[u] = ++time;
    for (int v : graph[u])
    {
        if (!visited[v])
        {
            findBridges(v, u, graph, visited, discovery, low, bridges, time);
            low[u] = min(low[u], low[v]);

            if (low[v] > discovery[u])
            {
                bridges.push_back({u, v});
            }
        }
        else if (v != parent)
        {
            low[u] = min(low[u], discovery[v]);
        }
    }
}

int main()
{
    int n, m;
    cout << "Enter the number of devices (nodes): ";
    cin >> n;
    cout << "Enter the number of connections (edges): ";
    cin >> m;

    vector<vector<Edge>> graph(n);
    vector<vector<int>> unweightedGraph(n);

    cout << "Enter the connections (node1 node2 weight):\n";
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
        unweightedGraph[u].push_back(v);
        unweightedGraph[v].push_back(u);
    }

    int start;
    cout << "Enter the starting device for optimization: ";
    cin >> start;

    vector<int> distances;
    dijkstra(start, graph, distances);

    cout << "Shortest distances from device " << start << ":\n";
    for (int i = 0; i < n; ++i)
    {
        cout << "Device " << i << ": " << (distances[i] == INF ? -1 : distances[i]) << endl;
    }
    vector<bool> visited(n, false);
    vector<int> discovery(n, -1), low(n, -1);
    vector<pair<int, int>> bridges;
    int time = 0;
    for (int i = 0; i < n; ++i)
    {
        if (!visited[i])
        {
            findBridges(i, -1, unweightedGraph, visited, discovery, low, bridges, time);
        }
    }
    cout << "Critical connections (bridges) in the network:\n";
    for (const auto& bridge : bridges) {
        cout << "Connection between " << bridge.first << " and " << bridge.second << endl;
    }

    return 0;
}

