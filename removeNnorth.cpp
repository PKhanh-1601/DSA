//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 05 - Part 2 - Exercise 04
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

void removeNthFromEnd(Node*& head, int n)
{
    Node* first = head;
    Node* second = head;

    for (int i = 0; i < n; i++)
    {
        if (first == NULL) return;
        first = first->next;
    }

    if (first == NULL)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return;
    }

    while (first->next)
        {
        first = first->next;
        second = second->next;
        }
    Node* temp = second->next;
    second->next = second->next->next;
    delete temp;
}

int main()
{
    Node* head = NULL;
    int n, value;
    cout << "Nhap so luong phan tu trong danh sach: ";
    cin >> n;
    cout << "Nhap cac phan tu cua danh sach: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> value;
        insertAtEnd(head, value);
    }

    cout << "Danh sach ban dau: ";
    printList(head);

    int removePos;
    cout << "Nhap vi tri node muon xoa tu cuoi: ";
    cin >> removePos;

    removeNthFromEnd(head, removePos);

    cout << "Danh sach sau khi xoa node: ";
    printList(head);
    return 0;
}
