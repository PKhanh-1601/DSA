//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 8
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;
class Graph
{
    int V;
    unordered_map<int, unordered_set<int>> adj;
public:
    Graph(int V) : V(V) {}
    void addEdge(int u, int v)
    {
        adj[u].insert(v);
        adj[v].insert(u);
    }
    double modularity(const unordered_map<int, int>& community)
    {
        double Q = 0.0;
        int m = 0;
        unordered_map<int, int> degree;
        for (const auto& node : adj)
        {
            m += node.second.size();
            degree[node.first] = node.second.size();
        }
        m /= 2;
        for (const auto& node : adj)
        {
            int u = node.first;
            for (int v : node.second)
            {
                if (community.at(u) == community.at(v))
                {
                    Q += 1.0 - (degree[u] * degree[v]) / (2.0 * m);
                }
            }
        }
        Q /= (2.0 * m);
        return Q;
    }
    unordered_map<int, int> louvain()
    {
        unordered_map<int, int> community;
        for (int i = 0; i < V; ++i)
        {
            community[i] = i;
        }
        bool improvement = true;
        while (improvement)
        {
            improvement = false;
            for (int u = 0; u < V; ++u)
            {
                int bestCommunity = community[u];
                double bestIncrease = 0.0;

                unordered_map<int, int> communityCount;
                for (int v : adj[u])
                {
                    communityCount[community[v]]++;
                }

                for (const auto& entry : communityCount)
                {
                    int c = entry.first;
                    community[u] = c;
                    double increase = modularity(community);
                    if (increase > bestIncrease)
                    {
                        bestIncrease = increase;
                        bestCommunity = c;
                    }
                }
                if (bestCommunity != community[u])
                {
                    community[u] = bestCommunity;
                    improvement = true;
                }
            }
        }
        return community;
    }
};

int main() {
    Graph g(6);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 0);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 3);
    unordered_map<int, int> communities = g.louvain();
    cout << "Communities in the graph:\n";
    for (const auto& entry : communities)
    {
        cout << "Node " << entry.first << " is in community " << entry.second << endl;
    }
    return 0;
}
