//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 2 - Exercise 07
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int value;
    Node* link;
    Node(int x) : value(x), link(NULL) {}
};

struct List
{
    Node* head;
    List() : head(NULL) {}
};

void insertAtEnd(List& A, int value)
{
    Node* newNode = new Node(value);
    if (!A.head)
    {
        A.head = newNode;
    }
    else
    {
        Node* temp = A.head;
        while (temp->link)
        {
            temp = temp->link;
        }
        temp->link = newNode;
    }
}
void printList(Node* head)
{
    while (head)
    {
        cout << head->value << " ";
        head = head->link;
    }
    cout << endl;
}

void removeZeroSumNodes(List& A)
{
    Node* dummy = new Node(0);
    dummy->link = A.head;
    Node* prev = dummy;
    Node* current = A.head;

    while (current != NULL)
        {
        int sum = 0;
        Node* tmp = current;

        while (tmp != NULL)
            {
            sum += tmp->value;

            if (sum == 0)
                {
                prev->link = tmp->link;
                current = prev->link;
                break;
                }
            tmp = tmp->link;
        }

        if (tmp == NULL)
        {
            // If no zero-sum was found, move prev and current
            prev = current;
            current = current->link;
        }
    }

    A.head = dummy->link;
    delete dummy;
}

int main()
{
    List A;
    int n, value;
    cout << "Nhap so luong phan tu trong danh sach: ";
    cin >> n;
    cout << "Nhap cac phan tu cua danh sach: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> value;
        insertAtEnd(A, value);
    }
    cout << "Danh sach ban dau: ";
    printList(A.head);
    removeZeroSumNodes(A);

    cout << "Danh sach sau khi xoa cac node co tong bang 0: ";
    printList(A.head);

    return 0;
}
