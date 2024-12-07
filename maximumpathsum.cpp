//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 9
//Notes or Remarks:

#include <iostream>
#include <queue>
#include <algorithm>
#include <climits>
#include <vector>
#include <sstream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution
{
public:
    int maxPathSum(TreeNode* root)
    {
        int maxSum = INT_MIN;
        findMaxPathSum(root, maxSum);
        return maxSum;
    }

private:
    int findMaxPathSum(TreeNode* node, int& maxSum)
   {
        if (!node) return 0;
        int leftSum = max(0, findMaxPathSum(node->left, maxSum));
        int rightSum = max(0, findMaxPathSum(node->right, maxSum));
        maxSum = max(maxSum, leftSum + rightSum + node->val);
        return node->val + max(leftSum, rightSum);
    }
};

int stringToInt(const string& s)
{
    stringstream ss(s);
    int num;
    ss >> num;
    return num;
}

TreeNode* buildTree(const vector<int>& values)
{
    if (values.empty() || values[0] == -1)
    {
        return NULL;
    }
    TreeNode* root = new TreeNode(values[0]);
    queue<TreeNode*> q;
    q.push(root);
    size_t i = 1;
    while (!q.empty() && i < values.size())
    {
        TreeNode* current = q.front();
        q.pop();

        if (values[i] != -1)
        {
            current->left = new TreeNode(values[i]);
            q.push(current->left);
        }
        i++;

        if (i < values.size() && values[i] != -1)
        {
            current->right = new TreeNode(values[i]);
            q.push(current->right);
        }
        i++;
    }
    return root;
}

int main() {
    cout << "Nhap cac gia tri cua cay nhi phan theo thu tu cap bac (dung -1 de bieu dien nut rong, cach nhau bang khoang trang):\n";
    string input;
    getline(cin, input);
    vector<int> values;
    stringstream ss(input);
    string temp;
    while (ss >> temp)
    {
        values.push_back(stringToInt(temp));
    }
    TreeNode* root = buildTree(values);
    Solution solution;
    cout << "Maximum Path Sum: " << solution.maxPathSum(root) << endl;
    return 0;
}
