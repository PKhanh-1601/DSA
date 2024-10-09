//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 02 - Part 1 - Lab2
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

class Node
{
public:
    int data;
    Node* next;

    Node(int data)
    {
        this->data = data;
        this->next = NULL;
    }
};

class Stack
{
public:
    Node *top = NULL;
    void push(int data)
    {
        Node* newNode = new Node(data);
        if (top == NULL)
        {
            top = newNode;
        }
        else
        {
            newNode->next = top;
            top = newNode;
        }
    }

    void pop()
    {
        if (top == NULL)
        {
            cout << "Stack is empty, cannot pop.\n";
            return;
        }
        else
        {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty()
    {
        return top == NULL;
    }

    bool isFull()
    {
        return false;
    }

    void print()
    {
        if (isEmpty())
        {
            cout << "Stack is empty\n";
        }
        else
        {
            Node* temp = top;
            while (temp != NULL)
            {
                cout << temp->data << " ";
                temp = temp->next;
            }
            cout << endl;
        }
    }
    bool isValidBracketSequence(string s)
    {
        Stack stack;
        for (char c : s)
            {
            if (c == '(' || c == '[' || c == '{')
            {
                stack.push(c);
            }
        else if (c == ')' || c == ']' || c == '}')
            {
                if (stack.isEmpty()) return false;
                char topChar = stack.top->data;
                if ((c == ')' && topChar == '(') || (c == ']' && topChar == '[') || (c == '}' && topChar == '{')) {
                    stack.pop();
                }
        else
                {
                    return false;
                }
            }
        }
        return stack.isEmpty();
    }

    string reverseWords(string str)
    {
        Stack stack;
        string result = "", word = "";
        for (char c : str)
        {
            if (c == ' ')
            {
                while (!stack.isEmpty())
                {
                    result += stack.top->data;
                    stack.pop();
                }
                result += ' ';
            }
        else
            {
                stack.push(c);
            }
        }

        while (!stack.isEmpty())
        {
            result += stack.top->data;
            stack.pop();
        }
        return result;
    }
};

void displayMenu()
{
    cout << "\nMenu:\n";
    cout << "1. Push several numbers onto the stack\n";
    cout << "2. Check if the stack is empty\n";
    cout << "3. Check if the stack is full\n";
    cout << "4. Check if a bracket sequence is valid\n";
    cout << "5. Reverse words in a string\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    Stack stack;
    int choice, inputNumber;

    do
    {
        displayMenu();
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                cout << "Enter several integers to push onto the stack (0 to stop): ";
                while (true)
                {
                    cin >> inputNumber;
                    if (inputNumber == 0) break;
                    stack.push(inputNumber);
                }
                stack.print();
                break;
            }
            case 2:
                if (stack.isEmpty())
                    cout << "Stack is empty.\n";
                else
                    cout << "Stack is not empty.\n";
                break;

            case 3:
                if (stack.isFull())
                    cout << "Stack is full.\n";
                else
                    cout << "Stack is not full.\n";
                break;

            case 4:
            {
                cout << "Enter a bracket sequence: ";
                string bracketSequence;
                cin >> bracketSequence;
                if (stack.isValidBracketSequence(bracketSequence))
                {
                    cout << "The bracket sequence is valid.\n";
                }
                else
                {
                    cout << "The bracket sequence is invalid.\n";
                }
                break;
            }

            case 5:
            {
                cin.ignore();
                cout << "Enter a string to reverse words: ";
                string inputString;
                getline(cin, inputString);
                cout << stack.reverseWords(inputString) << endl;
                break;
            }
            case 6:
                cout << "Exiting the program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
    while (choice != 6);

    return 0;
}

