//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 10
//Notes or Remarks:

#include <iostream>
#include <cstdlib>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

int findIndex(int* inorder, int start, int end, int value)
{
    for (int i = start; i <= end; ++i)
    {
        if (inorder[i] == value)
            return i;
    }
    return -1;
}

TreeNode* buildTree(int* inorder, int* postorder, int inorderStart, int inorderEnd, int& postIndex)
{
    if (inorderStart > inorderEnd)
    {
        return NULL;
    }
    int rootVal = postorder[postIndex--];
    TreeNode* root = new TreeNode(rootVal);
    if (inorderStart == inorderEnd)
    {
        return root;
    }
    int inorderIndex = findIndex(inorder, inorderStart, inorderEnd, rootVal);
    root->right = buildTree(inorder, postorder, inorderIndex + 1, inorderEnd, postIndex);
    root->left = buildTree(inorder, postorder, inorderStart, inorderIndex - 1, postIndex);
    return root;
}

void preorderTraversal(TreeNode* root)
{
    if (root == NULL)
    {
        return;
    }
       cout << root->val << " ";
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

int main()
{
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;
    int* inorder = new int[n];
    int* postorder = new int[n];
    cout << "Enter the inorder traversal: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> inorder[i];
    }
    cout << "Enter the postorder traversal: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> postorder[i];
    }
    int postIndex = n - 1;
    TreeNode* root = buildTree(inorder, postorder, 0, n - 1, postIndex);
    cout << "Preorder traversal of the reconstructed tree: ";
    preorderTraversal(root);
    delete[] inorder;
    delete[] postorder;
    return 0;
}
