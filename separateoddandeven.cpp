//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 05 - Part 2 - Exercise 05
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

void separateOddEven(Node* head, Node*& oddHead, Node*& evenHead)
{
    Node* oddTail = NULL;
    Node* evenTail = NULL;
    int index = 0;

    while (head)
    {
        if (index % 2 == 0)
        {
            if (!evenHead)
            {
                evenHead = head;
                evenTail = evenHead;
            }
    else
            {
                evenTail->next = head;
                evenTail = evenTail->next;
            }
        }
        else
        {
            if (!oddHead)
            {
                oddHead = head;
                oddTail = oddHead;
            }
    else
            {
                oddTail->next = head;
                oddTail = oddTail->next;
            }
        }
        head = head->next;
        index++;
    }

    if (evenTail) evenTail->next = NULL;
    if (oddTail) oddTail->next = NULL;
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

    Node* oddHead = NULL;
    Node* evenHead = NULL;

    separateOddEven(head, oddHead, evenHead);

    cout << "Danh sach cac node o vi tri le: ";
    printList(oddHead);

    cout << "Danh sach cac node o vi tri chan: ";
    printList(evenHead);

    return 0;
}
