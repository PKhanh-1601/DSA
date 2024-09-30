//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 06
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* appendNode(ListNode*& head, int data)
{
    ListNode* newNode = new ListNode(data);
    if (head == NULL)
    {
        head = newNode;
    }
    else
    {
        ListNode* temp = head;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    return newNode;
}

void printList(ListNode* head)
{
    while (head != NULL)
    {
        cout << head->val << " ";
        head = head->next;
    }
    cout << endl;
}

ListNode* eliminateDuplicates(ListNode* head)
{
    if (head == NULL) return head;
    ListNode* current = head;
    while (current != NULL && current->next != NULL)
    {
        if (current->val == current->next->val)
        {
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
        }
    else
        {
            current = current->next;
        }
    }
    return head;
}

int main()
{
    ListNode* head = NULL;
    int n, x;
    cout << "Nhap so luong phan tu cua linked list: ";
    cin >> n;
    cout << "Nhap cac phan tu cua linked list (da sap xep): ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        appendNode(head, x);
    }
    cout << "Danh sach ban dau: ";
    printList(head);
    head = eliminateDuplicates(head);
    cout << "Danh sach sau khi loai bo cac phan tu trung lap: ";
    printList(head);
    return 0;
}
