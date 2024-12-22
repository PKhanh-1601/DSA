//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 9
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct TreeNode
{
    string name;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string value) : name(value), left(NULL), right(NULL) {}
};

class PhylogeneticTree
{
public:
    TreeNode* root;
    PhylogeneticTree() : root(NULL) {}
    TreeNode* insertRec(TreeNode* node, const string& name)
    {
        if (!node) return new TreeNode(name);
        if (name < node->name) node->left = insertRec(node->left, name);
        else node->right = insertRec(node->right, name);
        return node;
    }

    void insert(const string& name)
    {
        root = insertRec(root, name);
    }

    void printTree(TreeNode* node, int depth = 0)
    {
        if (!node) return;
        for (int i = 0; i < depth; ++i) cout << "  ";
        cout << node->name << endl;
        printTree(node->left, depth + 1);
        printTree(node->right, depth + 1);
    }
};

int main()
{
    PhylogeneticTree pt;
    pt.insert("Homo sapiens");
    pt.insert("Pan troglodytes");
    pt.insert("Gorilla gorilla");
    pt.insert("Pongo pygmaeus");
    pt.insert("Macaca mulatta");

    cout << "Tree structure:" << endl;
    pt.printTree(pt.root);

    return 0;
}
