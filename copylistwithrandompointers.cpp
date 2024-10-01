//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 2 - Exercise 02
//Notes or Remarks:

#include <iostream>
using namespace std;

struct Node
{
    int val;
    Node* next;
    Node* random;
    Node(int _val) : val(_val), next(NULL), random(NULL) {}
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

Node* copyRandomList(Node* head)
{
    if (!head) return NULL;

    Node* current = head;
    while (current)
    {
        Node* newNode = new Node(current->val);
        newNode->next = current->next;
        current->next = newNode;
        current = newNode->next;
    }

    current = head;
    while (current)
    {
        if (current->random)
        {
            current->next->random = current->random->next;
        }
        current = current->next->next;
    }

    Node* copyHead = head->next;
    current = head;
    Node* copyCurrent = copyHead;
    while (current)
    {
        current->next = current->next->next;
        if (copyCurrent->next)
        {
            copyCurrent->next = copyCurrent->next->next;
        }
        current = current->next;
        copyCurrent = copyCurrent->next;
    }
    return copyHead;
}

void printList(Node* head)
{
    while (head)
    {
        cout << "Value: " << head->val;
        if (head->random)
        {
            cout << ", Random points to: " << head->random->val;
        }
    else
        {
            cout << ", Random points to: null";
        }
        cout << endl;
        head = head->next;
    }
}

int main()
{
    Node* head = NULL;
    int n;

    cout << "Nhap so luong phan tu cua danh sach lien ket: ";
    cin >> n;
    cout << "Nhap cac phan tu cua danh sach:\n";
    for (int i = 0; i < n; ++i)
    {
        int value;
        cout << "Phan tu " << i + 1 << ": ";
        cin >> value;
        insertAtEnd(head, value);
    }

    cout << "Nhap cac lien ket random (nhap -1 neu khong co lien ket random):\n";
    Node* current = head;
    for (int i = 0; i < n; ++i)
    {
        int randomIndex;
        cout << "Random cho phan tu " << i + 1 << ": ";
        cin >> randomIndex;

        if (randomIndex != -1)
        {
            Node* randomNode = head;
            for (int j = 0; j < randomIndex; ++j)
            {
                randomNode = randomNode->next;
            }
            current->random = randomNode;
        }
        current = current->next;
    }

    Node* copiedList = copyRandomList(head);

    cout << "\nDanh sach goc:\n";
    printList(head);

    cout << "\nDanh sach da sao chep:\n";
    printList(copiedList);

    return 0;
}
