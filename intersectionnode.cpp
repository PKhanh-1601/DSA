//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 04
//Notes or Remarks:

#include <iostream>
using namespace std;

struct node {
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
        cout << "Danh sach: ";
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->link;
        }
        cout << endl;
    }

    int length()
    {
        int len = 0;
        node *current = phead;
        while (current != NULL) {
            len++;
            current = current->link;
        }
        return len;
    }

    node* findIntersection(List& other)
    {
        int len1 = this->length();
        int len2 = other.length();

        node* ptr1 = this->phead;
        node* ptr2 = other.phead;

        if (len1 > len2)
        {
            for (int i = 0; i < len1 - len2; i++)
            {
                ptr1 = ptr1->link;
            }
        }
        else
        {
            for (int i = 0; i < len2 - len1; i++)
            {
                ptr2 = ptr2->link;
            }
        }

        while (ptr1 != NULL && ptr2 != NULL)
        {
            if (ptr1 == ptr2)
            {
                return ptr1;
            }
            ptr1 = ptr1->link;
            ptr2 = ptr2->link;
        }

        return NULL;
    }
};

int main() {
    List l1, l2;

    // Input for the first linked list
    int n1;
    cout << "Nhap so phan tu cho danh sach 1: ";
    cin >> n1;
    cout << "Nhap gia tri cho danh sach 1: ";
    for (int i = 0; i < n1; i++) {
        int x;
        cin >> x;
        l1.insertList(x);
    }

    // Input for the second linked list
    int n2;
    cout << "Nhap so phan tu cho danh sach 2: ";
    cin >> n2;
    cout << "Nhap gia tri cho danh sach 2: ";
    for (int i = 0; i < n2; i++) {
        int x;
        cin >> x;
        l2.insertList(x);
    }

    node* intersection = l1.findIntersection(l2);

    if (intersection != NULL) {
        cout << "Diem giao nhau: " << intersection->data << endl;
    } else {
        cout << "Khong co giao nhau." << endl;
    }

    return 0;
}
