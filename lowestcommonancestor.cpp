//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 7
//Notes or Remarks:

#include <iostream>
#include <queue>
#include <vector>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

TreeNode* insertIntoBST(TreeNode* root, int val)
{
    if (!root)
    {
        return new TreeNode(val);
    }
    if (val < root->val)
    {
        root->left = insertIntoBST(root->left, val);
    }
    else
    {
        root->right = insertIntoBST(root->right, val);
    }
    return root;
}

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
{
    if (!root)
    {
        return NULL;
    }
    if (p->val < root->val && q->val < root->val)
    {
        return lowestCommonAncestor(root->left, p, q);
    }
    if (p->val > root->val && q->val > root->val)
    {
        return lowestCommonAncestor(root->right, p, q);
    }
    return root;
}

TreeNode* findNode(TreeNode* root, int val)
{
    if (!root || root->val == val)
    {
        return root;
    }
    if (val < root->val)
    {
        return findNode(root->left, val);
    }
    return findNode(root->right, val);
}

int main()
{
    TreeNode* root = NULL;

    cout << "Nhap cac gia tri cua cay BST (dung -1 de ket thuc): ";
    int val;
    while (true)
    {
        cin >> val;
        if (val == -1) break;
        root = insertIntoBST(root, val);
    }

    cout << "Nhap gia tri cua nut thu nhat: ";
    int pVal;
    cin >> pVal;

    cout << "Nhap gia tri cua nut thu hai: ";
    int qVal;
    cin >> qVal;

    TreeNode* p = findNode(root, pVal);
    TreeNode* q = findNode(root, qVal);

    if (!p || !q)
    {
        cout << "Mot trong hai nut khong ton tai trong cay." << endl;
    }
    else
    {
        TreeNode* lca = lowestCommonAncestor(root, p, q);
        if (lca)
        {
            cout << "Lowest Common Ancestor cua " << pVal << " va " << qVal << " la: " << lca->val << endl;
        }
    else
        {
            cout << "Khong tim thay Lowest Common Ancestor." << endl;
        }
    }
    return 0;
}

