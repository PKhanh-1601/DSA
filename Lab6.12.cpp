//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 12
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <limits>

using namespace std;

class SocialNetwork
{
private:
    map<int, vector<int> > adjList;

public:
    void addUser(int user)
    {
        if (adjList.find(user) == adjList.end())
        {
            adjList[user] = vector<int>();
        }
    }
    void addFriendship(int user1, int user2)
    {
        adjList[user1].push_back(user2);
        adjList[user2].push_back(user1);
    }
    void displayNetwork()
    {
        cout << "Social Network:" << endl;
        for (const auto& pair : adjList)
        {
            cout << pair.first << ": ";
            for (int friendId : pair.second)
            {
                cout << friendId << " ";
            }
            cout << endl;
        }
    }
    void calculateDegreeCentrality()
    {
        cout << "\nDegree Centrality:" << endl;
        for (const auto& pair : adjList)
        {
            cout << "User " << pair.first << ": " << pair.second.size() << endl;
        }
    }

    void detectCommunities()
    {
        set<int> visited;
        vector<vector<int> > communities;
        for (const auto& pair : adjList)
        {
            int user = pair.first;
            if (visited.find(user) == visited.end())
            {
                vector<int> community;
                queue<int> q;
                q.push(user);
                visited.insert(user);

                while (!q.empty())
                {
                    int current = q.front();
                    q.pop();
                    community.push_back(current);

                    for (int neighbor : adjList[current])
                    {
                        if (visited.find(neighbor) == visited.end())
                        {
                            visited.insert(neighbor);
                            q.push(neighbor);
                        }
                    }
                }
                communities.push_back(community);
            }
        }
        cout << "\nDetected Communities:" << endl;
        for (size_t i = 0; i < communities.size(); ++i) {
            cout << "Community " << i + 1 << ": ";
            for (int user : communities[i]) {
                cout << user << " ";
            }
            cout << endl;
        }
    }
};

int main()
{
    SocialNetwork network;
    int choice;

    while (true)
    {
        cout << "\nSocial Network Menu:\n";
        cout << "1. Add User\n";
        cout << "2. Add Friendship\n";
        cout << "3. Display Network\n";
        cout << "4. Calculate Degree Centrality\n";
        cout << "5. Detect Communities\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            int user;
            cout << "Enter user ID: ";
            cin >> user;
            network.addUser(user);
        }
        else if (choice == 2)
        {
            int user1, user2;
            cout << "Enter two user IDs to create a friendship: ";
            cin >> user1 >> user2;
            network.addFriendship(user1, user2);
        }
        else if (choice == 3)
        {
            network.displayNetwork();
        }
        else if (choice == 4)
        {
            network.calculateDegreeCentrality();
        }
        else if (choice == 5)
        {
            network.detectCommunities();
        }
        else if (choice == 6)
        {
            break;
        }
        else
        {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return 0;
}
