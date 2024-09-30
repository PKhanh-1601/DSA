//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 0
//Notes or Remarks:

#include <iostream>
#include <vector>
using namespace std;

struct node
{
    int data;
    node *link;
};

struct List {
    node *phead = NULL;
    node *ptail = NULL;

    void insertList(int data)
    {
        if (phead == NULL)
        {
            node *tmp = new node();
            tmp->data = data;
            tmp->link = NULL;
            phead = tmp;
            ptail = tmp;
        }
        else
        {
            node *temp = new node();
            temp->data = data;
            temp->link = NULL;
            ptail->link = temp;
            ptail = temp;
        }
    }

    void print()
    {
        node *tmp = phead;
        if (tmp == NULL)
        {
            cout << "Danh sach rong." << endl;
            return;
        }
        cout << "Danh sach vua nhap la: ";
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->link;
        }
        cout << endl;
    }

    vector<node*> search(int X) {
        vector<node*> addresses;
        node *current = phead;

        while (current != NULL)
        {
            if (current->data == X)
            {
                addresses.push_back(current);
            }
            current = current->link;
        }

        return addresses;
    }
};

int main()
{
    List l;
    int n;
    cout << "Nhap so phan tu: ";
    cin >> n;
    cout << "Nhap gia tri: ";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        l.insertList(x);
    }

    l.print();

    int searchValue;
    cout << "Nhap gia tri X de tim: ";
    cin >> searchValue;

    vector<node*> foundNodes = l.search(searchValue);

    if (!foundNodes.empty())
    {
        cout << "Dia chi cac node co gia tri " << searchValue << ": " << endl;
        for (node* addr : foundNodes) {
            cout << addr << " (Gia tri: " << addr->data << ")" << endl;
        }
    }
    else
    {
        cout << "Khong tim thay node co gia tri " << searchValue << "." << endl;
    }

    return 0;
}
