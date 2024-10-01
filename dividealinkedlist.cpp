//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 2 - Exercise 06
//Notes or Remarks:

#include <iostream>
#include <vector>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

int countNodes(ListNode* head)
{
    int count = 0;
    while (head)
    {
        count++;
        head = head->next;
    }
    return count;
}

vector<ListNode*> splitListToParts(ListNode* root, int k)
{
    vector<ListNode*> parts(k, NULL);
    int totalNodes = countNodes(root);
    int nodesPerPart = totalNodes / k;
    int extraNodes = totalNodes % k;

    ListNode* current = root;
    for (int i = 0; i < k && current; i++)
    {
        parts[i] = current;
        int partSize = nodesPerPart + (i < extraNodes ? 1 : 0);

        for (int j = 1; j < partSize; j++)
        {
            if (current) current = current->next;
        }

        if (current)
        {
            ListNode* nextPart = current->next;
            current->next = NULL;
            current = nextPart;
        }
    }
    return parts;
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
    int n, k;
    cout << "Nhap so luong phan tu cua danh sach lien ket: ";
    cin >> n;

    ListNode* head = NULL;
    ListNode* tail = NULL;
    cout << "Nhap cac phan tu cua danh sach lien ket:\n";
    for (int i = 0; i < n; i++)
    {
        int x;
        cin >> x;
        ListNode* newNode = new ListNode(x);
        if (!head)
        {
            head = newNode;
            tail = newNode;
        }
    else
        {
            tail->next = newNode;
            tail = newNode;
        }
    }
    cout << "Nhap so phan k can chia: ";
    cin >> k;

    vector<ListNode*> result = splitListToParts(head, k);

    for (int i = 0; i < k; i++)
    {
        cout << "Phần " << i + 1 << ": ";
        printList(result[i]);
    }
    return 0;
}
