//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 04
//Notes or Remarks:

#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

int getLength(ListNode* head)
{
    int length = 0;
    while (head != NULL)
    {
        length++;
        head = head->next;
    }
    return length;
}

ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
    int lenA = getLength(headA);
    int lenB = getLength(headB);
    while (lenA > lenB)
    {
        headA = headA->next;
        lenA--;
    }
    while (lenB > lenA)
    {
        headB = headB->next;
        lenB--;
    }
    while (headA != NULL && headB != NULL)
    {
        if (headA == headB)
        {
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
    }
    return NULL;
}

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

int main()
{
    ListNode* headA = NULL;
    ListNode* headB = NULL;
    int n1, n2, x;
    cout << "Nhap so luong phan tư cua linked list A: ";
    cin >> n1;
    cout << "Nhap cac phan tư linked list A: ";
    for (int i = 0; i < n1; i++)
    {
        cin >> x;
        appendNode(headA, x);
    }
    cout << "Nhap so luong phan tư cua linked list B: ";
    cin >> n2;
    cout << "Nhap cac phan tu linked list B: ";
    for (int i = 0; i < n2; i++)
    {
        cin >> x;
        appendNode(headB, x);
    }
    int intersectionVal;
    cout << "Nhap gia tri Node ma hai danh sach giao nhau (trong linked list A): ";
    cin >> intersectionVal;
    ListNode* temp = headA;
    while (temp != NULL && temp->val != intersectionVal)
    {
        temp = temp->next;
    }
    if (temp != NULL)
    {
        ListNode* tailB = headB;
        while (tailB->next != NULL)
        {
            tailB = tailB->next;
        }
        tailB->next = temp;
    }
    ListNode* intersectionNode = getIntersectionNode(headA, headB);

    if (intersectionNode != NULL)
    {
        cout << "Giao diem tai Node co gia tri: " << intersectionNode->val << endl;
    }
    else
    {
        cout << "Khong co giao diem." << endl;
    }

    return 0;
}
