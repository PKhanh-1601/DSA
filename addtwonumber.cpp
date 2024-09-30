//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 05 - Part 2 - Exercise 01
//Notes or Remarks:

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
    Node(int x) : data(x), next(NULL) {}
};

void insertAtEnd(Node*& head, int value)
{
    Node* newNode = new Node(value);
    if (!head)
    {
        head = newNode;
    } else
    {
        Node* temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void printList(Node* head)
{
    while (head)
    {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

Node* searchForValue(Node* head, int X)
{
    Node* current = head;
    bool found = false;

    while (current != NULL)
    {
        if (current->data == X)
        {
            cout << "Tim thay gia tri " << X << " tai dia chi: " <<current ;
            found = true;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << "NULL";
        return NULL;
    }

    return head;
}

int main()
{
    Node* head = NULL;
    int n,a,b;
    cout << "Nhap so luong phan tu trong danh sach: ";
    cin >> n;
    cout << "Nhap cac phan tu cua danh sach: ";
    for (int i = 0; i < n; ++i)
    {
        int data;
        cin >> data;
        insertAtEnd(head, data);
    }
    cout<<"Enter the two numbers: ";
    cin>>a>>b;
     insertAtEnd(head, a);
     insertAtEnd(head, b);
    cout<<"List after added: ";
    printList(head);
}
