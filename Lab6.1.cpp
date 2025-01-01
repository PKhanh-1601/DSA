//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 1
//Notes or Remarks:

#include <iostream>
#include <vector>
using namespace std;

class Graph
{
private:
    vector<vector<int> > adjacencyList;
    vector<vector<int> > adjacencyMatrix;
    int numVertices;

    void resizeMatrix()
    {
        for (int i = 0; i < adjacencyMatrix.size(); i++)
        {
            adjacencyMatrix[i].push_back(0);
        }
        adjacencyMatrix.push_back(vector<int>(numVertices, 0));
    }

public:
    Graph() : numVertices(0) {}

    void addVertex()
    {
        numVertices++;
        adjacencyList.push_back(vector<int>());
        resizeMatrix();
    }

    void addEdge(int u, int v)
    {
        if (u >= numVertices || v >= numVertices)
        {
            cout << "Error: Vertex does not exist.\n";
            return;
        }
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u);
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1;
    }

    void displayAdjList()
    {
        cout << "Adjacency List:\n";
        for (int i = 0; i < adjacencyList.size(); i++)
        {
            cout << i << ": ";
            for (int neighbor : adjacencyList[i])
            {
                cout << neighbor << " ";
            }
            cout << "\n";
        }
    }

    void displayAdjMatrix()
    {
        cout << "Adjacency Matrix:\n";
        for (auto &row : adjacencyMatrix)
        {
            for (int val : row)
            {
                cout << val << " ";
            }
            cout << "\n";
        }
    }
};

int main()
{
    Graph graph;
    int choice;

    while (true)
    {
        cout << "\nMenu:\n";
        cout << "1. Add Vertex\n";
        cout << "2. Add Edge\n";
        cout << "3. Display Adjacency List\n";
        cout << "4. Display Adjacency Matrix\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            graph.addVertex();
            cout << "A new vertex has been added.\n";
        }
        else if (choice == 2)
        {
            int u, v;
            cout << "Enter starting vertex (u): ";
            cin >> u;
            cout << "Enter ending vertex (v): ";
            cin >> v;
            graph.addEdge(u, v);
        }
        else if (choice == 3)
        {
            graph.displayAdjList();
        }
        else if (choice == 4)
        {
            graph.displayAdjMatrix();
        }
        else if (choice == 5)
        {
            cout << "Exiting the program.\n";
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
