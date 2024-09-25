#include<bits/stdc++.h>
using namespace std;

struct Node
{
    int data;
    Node* next;

    Node(int val)
    {
        data = val;
        next = NULL;
    }
};

void append(Node*& head, int newData)
{
    Node* newNode = new Node(newData);
    if (head == NULL)
    {
        head = newNode;
        return;
    }
    Node* last = head;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

void printList(Node* head)
{
    Node* temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

Node* findMiddle(Node* head)
{
    if (head == NULL)
    {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

int main()
{
    Node* head = NULL;
    int n;
    cout << "Nhap so phan tu cua danh sach lien ket: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        int value;
        cout << "Nhap phan tu " << i + 1 << ": ";
        cin >> value;
        append(head, value);
    }
    cout << "Danh sach lien ket da nhap: ";
    printList(head);
    Node* middle = findMiddle(head);
    if (middle != NULL)
    {
        cout << "Phan tu giua cua danh sach: " << middle->data << endl;
    } else
    {
        cout << "Danh sach lien ket rong." << endl;
    }

    return 0;
}
