//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 6
//Notes or Remarks:

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int checkHeight(TreeNode* root, bool& isBalanced)
{
    if (root == NULL)
    {
        return 0;
    }

    int leftHeight = checkHeight(root->left, isBalanced);
    int rightHeight = checkHeight(root->right, isBalanced);

    if (abs(leftHeight - rightHeight) > 1)
    {
        isBalanced = false;
    }
    return 1 + max(leftHeight, rightHeight);
}

bool isHeightBalanced(TreeNode* root)
{
    bool isBalanced = true;
    checkHeight(root, isBalanced);
    return isBalanced;
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

int stringToInt(const string& s)
{
    stringstream ss(s);
    int num;
    ss >> num;
    return num;
}

int main()
{
    cout << "Nhap cac gia tri cua cay nhi phan (dung -1 de bieu dien nut rong, cach nhau boi khoang trang):\n";
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

    if (isHeightBalanced(root))
    {
        cout << "Cay nhi phan CAN BANG." << endl;
    }
    else
    {
        cout << "Cay nhi phan KHONG CAN BANG." << endl;
    }

    return 0;
}
