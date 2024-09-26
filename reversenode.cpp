//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 02
//Notes or Remarks:

#include<bits/stdc++.h>
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
    } else
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

ListNode* reverseList(ListNode* head)
{
    ListNode* prev = NULL;
    ListNode* current = head;
    ListNode* next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

int main()
{
    ListNode* head = NULL;
    int n, x;
    cout << "Nhap so luong phan tu cua linked list: ";
    cin >> n;
    cout << "Nhap cac phan tu cua linked list: ";
    for (int i = 0; i < n; i++)
    {
        cin >> x;
        appendNode(head, x);
    }
    cout << "Danh sach ban dau: ";
    printList(head);
    head = reverseList(head);
    cout << "Danh sach sau khi dao nguoc: ";
    printList(head);

    return 0;
}
