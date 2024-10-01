//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 2 - Exercise 08
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

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
        head = newNode;  // Nếu danh sách rỗng, gán giá trị đầu tiên cho head
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

void generateRandomList(ListNode*& head)
{
    srand(time(0));
    int numEntries = rand() % 21 + 39;

    for (int i = 0; i < numEntries; ++i)
    {
        int randomValue = rand() % 199 - 99;
        insertAtEnd(head, randomValue);
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
    generateRandomList(head);
    cout << "Danh sach lien ket da duoc tao tu dong:\n";
    printList(head);

    return 0;
}
