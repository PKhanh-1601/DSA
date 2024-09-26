//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 02
//Notes or Remarks:

#include <bits/stdc++.h>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

bool isPalindrome(ListNode* head)
{
    vector<int> values;
    ListNode* current = head;
    while (current != NULL)
    {
        values.push_back(current->val);
        current = current->next;
    }

    int left = 0, right = values.size() - 1;
    while (left < right)
    {
        if (values[left] != values[right])
        {
            return false;
        }
        left++;
        right--;
    }
    return true;
}

ListNode* createLinkedList(const vector<int>& values)
{
    if (values.empty())
        return NULL;

    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;

    for (size_t i = 1; i < values.size(); ++i)
    {
        current->next = new ListNode(values[i]);
        current = current->next;
    }

    return head;
}

void deleteLinkedList(ListNode* head)
{
    while (head != NULL)
    {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    int n;
    cout << "Nhap so phan tu trong danh sach lien ket: ";
    cin >> n;

    vector<int> values(n);
    cout << "Nhap cac gia tri cua danh sach lien ket: ";
    for (int i = 0; i < n; ++i)
    {
        cin >> values[i];
    }

    ListNode* head = createLinkedList(values);

    if (isPalindrome(head))
    {
        cout << "The linked list is a palindrome." << endl;
    }
    else
    {
        cout << "The linked list is not a palindrome." << endl;
    }
    deleteLinkedList(head);
    return 0;
}
