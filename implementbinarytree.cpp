//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 1 - Classwork 1
//Notes or Remarks:

#include <iostream>
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

    Node* searchRecursive(Node* current, int value)
    {
        if (current == NULL || current->data == value)
        {
            return current;
        }
        if (value < current->data)
        {
            return searchRecursive(current->left, value);
        }
        return searchRecursive(current->right, value);
    }

    Node* findMin(Node* node)
    {
        Node* current = node;
        while (current && current->left != NULL)
        {
            current = current->left;
        }
        return current;
    }

    Node* deleteRecursive(Node* current, int value)
    {
        if (current == NULL)
        {
            return NULL;
        }
        if (value < current->data)
        {
            current->left = deleteRecursive(current->left, value);
        }
        else if (value > current->data)
        {
            current->right = deleteRecursive(current->right, value);
        }
        else
        {
            if (current->left == NULL)
            {
                Node* temp = current->right;
                delete current;
                return temp;
            }
        else if (current->right == NULL)
            {
                Node* temp = current->left;
                delete current;
                return temp;
            }
            Node* temp = findMin(current->right);
            current->data = temp->data;
            current->right = deleteRecursive(current->right, temp->data);
        }
        return current;
    }

    void inorderTraversalRecursive(Node* node)
    {
        if (node != NULL)
        {
            inorderTraversalRecursive(node->left);
            cout << node->data << " ";
            inorderTraversalRecursive(node->right);
        }
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
    bool search(int value)
    {
        return searchRecursive(root, value) != NULL;
    }
    void remove(int value)
    {
        root = deleteRecursive(root, value);
    }
    void display()
    {
        if (root == NULL)
        {
            cout << "Tree is empty" << endl;
            return;
        }
        inorderTraversalRecursive(root);
        cout << endl;
    }
};

int main()
{
    BinaryTree tree;
    int choice, value;
    while (true)
    {
        cout << "\nBinary Tree Operations:\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Display\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            case 1:
                cout << "Enter value to insert: ";
                cin >> value;
                tree.insert(value);
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> value;
                tree.remove(value);
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> value;
                if (tree.search(value))
                {
                    cout << "Value " << value << " found in the tree" << endl;
                }
                else
                {
                    cout << "Value " << value << " not found in the tree" << endl;
                }
                break;

            case 4:
                cout << "Tree contents (inorder traversal): ";
                tree.display();
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
