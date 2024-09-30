//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 05 - Part 2 - Exercise 03
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
    }
    else
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

void swapNodes(Node*& head, int x, int y)
{
    if (x == y) return;

    Node *prevX = NULL, *currX = head;
    while (currX && currX->data != x)
    {
        prevX = currX;
        currX = currX->next;
    }

    Node *prevY = NULL, *currY = head;
    while (currY && currY->data != y)
    {
        prevY = currY;
        currY = currY->next;
    }

    if (!currX || !currY) return;

    if (prevX)
    {
        prevX->next = currY;
    }
    else
    {
        head = currY;
    }

    if (prevY)
    {
        prevY->next = currX;
    }
    else
    {
        head = currX;
    }
    Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

int main() {
    Node* head = NULL;
    int n;
    cout << "Nhap so luong phan tu trong danh sach: ";
    cin >> n;
    cout << "Nhap cac phan tu cua danh sach: ";
    for (int i = 0; i < n; ++i) {
        int data;
        cin >> data;
        insertAtEnd(head, data);
    }

    cout << "Danh sach ban dau: ";
    printList(head);

    int x, y;
    cout << "Nhap gia tri cua hai node muon hoan doi: ";
    cin >> x >> y;

    swapNodes(head, x, y);

    cout << "Danh sach sau khi hoan doi: ";
    printList(head);

    return 0;
}

