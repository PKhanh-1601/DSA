//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 03
//Notes or Remarks:

#include <iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

typedef struct Node* node;

node MakeNode(int x)
{
    node tmp = new Node();
    tmp->data = x;
    tmp->next = NULL;
    return tmp;
}

void insertBack(node& a, int x)
{
    node tmp = MakeNode(x);
    if (a == NULL)
    {
        a = tmp;
    }
    else
    {
        node p = a;
        while (p->next != NULL)
        {
            p = p->next;
        }
        p->next = tmp;
    }
}

void printList(node head)
{
    node temp = head;
    while (temp != NULL)
    {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL" << endl;
}

node mergeTwoLists(node l1, node l2)
{
    node dummy = MakeNode(0);
    node current = dummy;
    while (l1 != NULL && l2 != NULL)
    {
        if (l1->data <= l2->data)
        {
            current->next = l1;
            l1 = l1->next;
        }
        else
        {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }
    if (l1 != NULL)
    {
        current->next = l1;
    }
    else
    {
        current->next = l2;
    }

    return dummy->next;
}

int main()
{
    node l1 = NULL, l2 = NULL;
    int n1, n2, x;
    cout << "Nhap so phan tu cua danh sach thu nhat: ";
    cin >> n1;
    for (int i = 0; i < n1; i++)
    {
        cout << "Nhap phan tu thu " << i + 1 << " cua danh sach thu nhat: ";
        cin >> x;
        insertBack(l1, x);
    }
    cout << "Nhap so phan tu cua danh sach thu hai: ";
    cin >> n2;
    for (int i = 0; i < n2; i++)
    {
        cout << "Nhap phan tu thu " << i + 1 << " cua danh sach thu hai: ";
        cin >> x;
        insertBack(l2, x);
    }
    cout << "Danh sach thu nhat: ";
    printList(l1);
    cout << "Danh sach thu hai: ";
    printList(l2);
    node mergedList = mergeTwoLists(l1, l2);
    cout << "Danh sach sau khi hop nhat: ";
    printList(mergedList);
    return 0;
}
