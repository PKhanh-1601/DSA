//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 5
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

void dijkstra(int source, const vector<vector<pair<int, int> > >& graph, int vertices)
{
    vector<int> distance(vertices, numeric_limits<int>::max());
    distance[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > pq;
    pq.push({0, source});
    while (!pq.empty())
    {
        int dist = pq.top().first;
        int current = pq.top().second;
        pq.pop();
        if (dist > distance[current])
            continue;
        for (const auto& edge : graph[current])
        {
            int neighbor = edge.first;
            int weight = edge.second;
            if (distance[current] + weight < distance[neighbor])
            {
                distance[neighbor] = distance[current] + weight;
                pq.push({distance[neighbor], neighbor});
            }
        }
    }
    cout << "Shortest distances from vertex " << source << ":\n";
    for (int i = 0; i < vertices; ++i)
    {
        cout << "Vertex " << i << ": ";
        if (distance[i] == numeric_limits<int>::max())
        {
            cout << "Infinity\n";
        }
    else
        {
            cout << distance[i] << "\n";
        }
    }
}

int main()
{
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;
    cout << "Enter the number of edges: ";
    cin >> edges;
    vector<vector<pair<int, int>>> graph(vertices);
    cout << "Enter edges in the format (source destination weight):\n";
    for (int i = 0; i < edges; ++i)
    {
        int source, destination, weight;
        cin >> source >> destination >> weight;
        graph[source].push_back({destination, weight});
    }
    int source;
    cout << "Enter the source vertex: ";
    cin >> source;
    dijkstra(source, graph, vertices);
    return 0;
}
