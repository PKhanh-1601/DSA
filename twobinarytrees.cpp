//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 13
//Notes or Remarks:

#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : val(value), left(NULL), right(NULL) {}
};

TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
    if (!t1) return t2;
    if (!t2) return t1;

    t1->val += t2->val;

    t1->left = mergeTrees(t1->left, t2->left);
    t1->right = mergeTrees(t1->right, t2->right);

    return t1;
}

TreeNode* insertNode(TreeNode* root, int value)
{
    if (!root)
    {
        return new TreeNode(value);
    }

    if (value < root->val)
    {
        root->left = insertNode(root->left, value);
    }
    else
    {
        root->right = insertNode(root->right, value);
    }

    return root;
}

void inorderTraversal(TreeNode* root)
{
    if (root)
    {
        inorderTraversal(root->left);
        cout << root->val << " ";
        inorderTraversal(root->right);
    }
}

int main()
{
    TreeNode* tree1 = NULL;
    TreeNode* tree2 = NULL;
    int choice, value;

    while (true)
    {
        cout << "\nBinary Tree Operations:\n";
        cout << "1. Insert into Tree 1\n";
        cout << "2. Insert into Tree 2\n";
        cout << "3. Merge Trees\n";
        cout << "4. Display Tree 1 (Inorder)\n";
        cout << "5. Display Tree 2 (Inorder)\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter value to insert into Tree 1: ";
                cin >> value;
                tree1 = insertNode(tree1, value);
                break;

            case 2:
                cout << "Enter value to insert into Tree 2: ";
                cin >> value;
                tree2 = insertNode(tree2, value);
                break;

            case 3:
                tree1 = mergeTrees(tree1, tree2);
                tree2 = NULL;
                cout << "Trees have been merged into Tree 1." << endl;
                break;

            case 4:
                cout << "Tree 1 (Inorder): ";
                inorderTraversal(tree1);
                cout << endl;
                break;

            case 5:
                cout << "Tree 2 (Inorder): ";
                inorderTraversal(tree2);
                cout << endl;
                break;

            case 6:
                cout << "Exiting program." << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}
