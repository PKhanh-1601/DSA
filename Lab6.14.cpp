//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 14
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cmath>
#include <algorithm>
using namespace std;

class RecommendationSystem
{
public:
    map<int, vector<int> > userItemGraph;

    void addInteraction(int user, int item)
    {
        userItemGraph[user].push_back(item);
    }
    map<int, double> calculateSimilarity(int targetUser)
    {
        map<int, double> similarity;
        set<int> targetItems(userItemGraph[targetUser].begin(), userItemGraph[targetUser].end());
        for (const auto& pair : userItemGraph)
        {
            int user = pair.first;
            const vector<int>& items = pair.second;
            if (user == targetUser) continue;
            set<int> userItems(items.begin(), items.end());
            vector<int> intersection, unionSet;

            set_intersection(targetItems.begin(), targetItems.end(),
                             userItems.begin(), userItems.end(),
                             back_inserter(intersection));

            set_union(targetItems.begin(), targetItems.end(),
                      userItems.begin(), userItems.end(),
                      back_inserter(unionSet));

            double jaccardSimilarity = unionSet.empty() ? 0.0 : (double)intersection.size() / unionSet.size();
            similarity[user] = jaccardSimilarity;
        }
        return similarity;
    }
    vector<int> recommendItems(int targetUser, int topN = 5)
    {
        map<int, double> similarity = calculateSimilarity(targetUser);
        map<int, double> itemScores;

        for (const auto& pair : similarity)
        {
            int user = pair.first;
            double sim = pair.second;

            for (int item : userItemGraph[user])
            {
                if (find(userItemGraph[targetUser].begin(), userItemGraph[targetUser].end(), item) == userItemGraph[targetUser].end()) {
                    itemScores[item] += sim;
                }
            }
        }

        vector<pair<int, double>> sortedItems(itemScores.begin(), itemScores.end());
        sort(sortedItems.begin(), sortedItems.end(), [](const pair<int, double>& a, const pair<int, double>& b)
        {
            return a.second > b.second;
        });
        vector<int> recommendations;
        for (int i = 0; i < min(topN, (int)sortedItems.size()); ++i)
        {
            recommendations.push_back(sortedItems[i].first);
        }
        return recommendations;
    }
};

int main()
{
    RecommendationSystem system;

    int numInteractions;
    cout << "Enter the number of user-item interactions: ";
    cin >> numInteractions;

    cout << "Enter each interaction as (user item):\n";
    for (int i = 0; i < numInteractions; ++i)
    {
        int user, item;
        cin >> user >> item;
        system.addInteraction(user, item);
    }

    int targetUser;
    cout << "Enter the target user ID for recommendations: ";
    cin >> targetUser;

    int topN;
    cout << "Enter the number of top recommendations to display: ";
    cin >> topN;

    vector<int> recommendations = system.recommendItems(targetUser, topN);

    cout << "Recommended items for user " << targetUser << ":\n";
    for (int item : recommendations)
    {
        cout << item << " ";
    }
    cout << endl;

    return 0;
}
