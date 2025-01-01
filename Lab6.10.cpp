//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 10
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;
typedef pair<int, int> pii;
vector<int> dijkstra(int start, int n, const vector<vector<pii> >& graph)
{
    vector<int> dist(n, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii> > pq;
    dist[start] = 0;
    pq.push({0, start});
    while (!pq.empty())
    {
        int currentDist = pq.top().first;
        int currentNode = pq.top().second;
        pq.pop();
        if (currentDist > dist[currentNode]) continue;
        for (const pii& neighbor : graph[currentNode])
        {
            int nextNode = neighbor.first;
            int weight = neighbor.second;
            if (dist[currentNode] + weight < dist[nextNode])
            {
                dist[nextNode] = dist[currentNode] + weight;
                pq.push({dist[nextNode], nextNode});
            }
        }
    }
    return dist;
}

int main()
{
    int n, m;
    cout << "Enter the number of nodes: ";
    cin >> n;
    cout << "Enter the number of edges: ";
    cin >> m;
    vector<vector<pii> > graph(n);
    cout << "Enter the edges in the format (u v w), where u and v are nodes (0-indexed) and w is the weight:\n";
    for (int i = 0; i < m; ++i)
    {
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    int start;
    cout << "Enter the starting node: ";
    cin >> start;
    vector<int> distances = dijkstra(start, n, graph);
    cout << "Shortest distances from node " << start << ":\n";
    for (int i = 0; i < n; ++i)
    {
        if (distances[i] == INT_MAX)
        {
            cout << "Node " << i << ": Unreachable\n";
        }
    else
        {
            cout << "Node " << i << ": " << distances[i] << "\n";
        }
    }
    return 0;
}

