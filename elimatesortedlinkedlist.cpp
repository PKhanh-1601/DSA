//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 06
//Notes or Remarks:

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void insertAtEnd(ListNode*& head, int value)
{
    ListNode* newNode = new ListNode(value);
    if (!head)
    {
        head = newNode;
    }
    else
    {
        ListNode* temp = head;
        while (temp->next)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void eliminateDuplicates(ListNode* head)
{
    ListNode* current = head;
    while (current && current->next)
    {
        if (current->val == current->next->val)
        {
            ListNode* duplicate = current->next;
            current->next = current->next->next;
            delete duplicate;
        }
    else
        {
            current = current->next;
        }
    }
}

void printList(ListNode* head)
{
    while (head)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}


int main()
{
    ListNode* head = NULL;
    int n;

    cout << "Nhap so luong phan tu cua danh sach lien ket (da sap xep): ";
    cin >> n;

    cout << "Nhap cac phan tu cua danh sach (theo thu tu tang dan):\n";
    for (int i = 0; i < n; ++i)
    {
        int value;
        cout << "Phan tu " << i + 1 << ": ";
        cin >> value;
        insertAtEnd(head, value);
    }

    eliminateDuplicates(head);

    cout << "Danh sach sau khi loai bo cac phan tu trung lap:\n";
    printList(head);

    return 0;
}
