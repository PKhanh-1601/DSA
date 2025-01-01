//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 9
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;
vector<double> pageRank(const vector<vector<int> >& graph, int iterations, double dampingFactor = 0.85)
{
    int n = graph.size();
    vector<double> rank(n, 1.0 / n);
    vector<int> outDegree(n, 0);
    for (int i = 0; i < n; ++i)
    {
        for (int j : graph[i])
        {
            outDegree[i]++;
        }
    }
    for (int iter = 0; iter < iterations; ++iter)
    {
        vector<double> newRank(n, (1.0 - dampingFactor) / n);
        for (int i = 0; i < n; ++i)
        {
            for (int j : graph[i])
            {
                if (outDegree[i] > 0)
                {
                    newRank[j] += dampingFactor * rank[i] / outDegree[i];
                }
            }
        }
        rank = newRank;
    }
    return rank;
}

int main()
{
    int n, m, iterations;
    double dampingFactor;
    cout << "Enter the number of web pages (nodes): ";
    cin >> n;
    cout << "Enter the number of links (edges): ";
    cin >> m;
    vector<vector<int> > graph(n);
    cout << "Enter the directed links (format: from to):\n";
    for (int i = 0; i < m; ++i)
    {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
    }
    cout << "Enter the number of iterations for convergence: ";
    cin >> iterations;
    cout << "Enter the damping factor (default 0.85): ";
    cin >> dampingFactor;
    vector<double> rank = pageRank(graph, iterations, dampingFactor);
    cout << "PageRank values after " << iterations << " iterations:\n";
    cout << fixed << setprecision(6);
    for (int i = 0; i < n; ++i)
    {
        cout << "Page " << i << ": " << rank[i] << "\n";
    }
    return 0;
}

