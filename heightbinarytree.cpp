//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 5
//Notes or Remarks:

#include <iostream>
#include <queue>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int calculateHeight(TreeNode* root)
{
    if (root == NULL)
    {
        return 0;
    }
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return 1 + max(leftHeight, rightHeight);
}

TreeNode* buildTree()
{
    cout << "Nhap gia tri cho goc cay (nhap -1 neu khong co): ";
    int val;
    cin >> val;

    if (val == -1)
    {
        return NULL;
    }

    TreeNode* root = new TreeNode(val);
    queue<TreeNode*> q;
    q.push(root);

    while (!q.empty())
    {
        TreeNode* current = q.front();
        q.pop();

        cout << "Nhap con trai cua " << current->val << " (nhap -1 neu khong co): ";
        cin >> val;
        if (val != -1)
        {
            current->left = new TreeNode(val);
            q.push(current->left);
        }

        cout << "Nhap con phai cua " << current->val << " (nhap -1 neu khong co): ";
        cin >> val;
        if (val != -1)
        {
            current->right = new TreeNode(val);
            q.push(current->right);
        }
    }
    return root;
}

int main()
{
    cout << "Tao cay nhi phan tu ban phim:\n";
    TreeNode* root = buildTree();
    cout << "Chieu cao cua cay nhi phan: " << calculateHeight(root) << endl;
    return 0;
}

