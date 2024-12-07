//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 4
//Notes or Remarks:

#include <iostream>
#include <algorithm>
using namespace std;

class Node
{
public:
    int data;
    Node* left;
    Node* right;

    Node(int value)
    {
        data = value;
        left = NULL;
        right = NULL;
    }
};

class BinaryTree
{
private:
    Node* root;
    Node* insertRecursive(Node* current, int value)
    {
        if (current == NULL)
        {
            return new Node(value);
        }

        if (value < current->data)
        {
            current->left = insertRecursive(current->left, value);
        }
        else if (value > current->data)
        {
            current->right = insertRecursive(current->right, value);
        }

        return current;
    }

    int heightForDiameter(Node* node, int& diameter)
    {
        if (node == NULL)
        {
            return 0;
        }
        int leftHeight = heightForDiameter(node->left, diameter);
        int rightHeight = heightForDiameter(node->right, diameter);
        diameter = max(diameter, leftHeight + rightHeight);
        return 1 + max(leftHeight, rightHeight);
    }
    void printTreeStructure(Node* root, string prefix = "", bool isLeft = false)
    {
        if (root == NULL)
        {
            return;
        }
        cout << prefix;
        cout << (isLeft ? "      " : "       ");
        cout << root->data << endl;
        printTreeStructure(root->left, prefix + (isLeft ? "    " : "    "), true);
        printTreeStructure(root->right, prefix + (isLeft ? "    " : "    "), false);
    }

public:
    BinaryTree()
    {
        root = NULL;
    }
    void insert(int value)
    {
        root = insertRecursive(root, value);
    }
    int getDiameter()
    {
        int diameter = 0;
        heightForDiameter(root, diameter);
        return diameter;
    }
    int getHeight(Node* node)
    {
        if (node == NULL)
        {
            return 0;
        }
        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    void displayTree()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        cout << "Tree structure:" << endl;
        printTreeStructure(root);
    }

    void analyzeDiameter()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        int diameter = getDiameter();
        cout << "Diameter of the tree: " << diameter << endl;
        cout << "This means the longest path between any two nodes has "
             << diameter << " edges" << endl;
        cout << "Maximum number of nodes in this path: " << diameter + 1 << endl;
    }
};

int main()
{
    BinaryTree tree;
    int choice, value;
    while (true)
    {
        cout << "\nBinary Tree Operations:\n";
        cout << "1. Insert Value\n";
        cout << "2. Calculate Diameter\n";
        cout << "3. Display Tree\n";
        cout << "4. Analyze Diameter\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                cout << "Value inserted successfully" << endl;
                break;

            case 2:
                cout << "Diameter of the tree: " << tree.getDiameter() << endl;
                break;

            case 3:
                tree.displayTree();
                break;

            case 4:
                tree.analyzeDiameter();
                break;

            case 5:
                cout << "Exiting program" << endl;
                return 0;

            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}

