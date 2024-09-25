//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 04 - Part 1 - Exercise 02
//Notes or Remarks:

#include <iostream>
using namespace std;

struct Node
{
  int data;
  Node *next;

  Node(int value) : data(value), next(NULL) {}
};

class List
{
  public:
    Node *head;
    Node *tail;
    List() : head(NULL), tail(NULL) {}

    bool detectCycle()
    {
      if (head == NULL) return false;

      Node *current = head;
      Node *prev = NULL;

      while (current != NULL)
      {
        if (current->next == prev)
        {
          return true;
        }

        Node *nextNode = current->next;
        current->next = prev;
        prev = current;
        current = nextNode;
      }
      return false;
    }

    void input()
    {
      int i = 0;
      while (true)
        {
        int inp;
        cin >> inp;
        if (inp == 0)
        {
          break;
        }

        Node *newNode = new Node(inp);
        newNode->data = inp;
        newNode->next = NULL;
        if (i == 0 || head == NULL)
        {
          head = newNode;
          tail = newNode;
        } else
        {
          tail->next = newNode;
          tail = newNode;
        }
        i++;
      }
    }

    void print()
    {
      Node *currNode = head;
      while (currNode != NULL)
      {
        cout << currNode->data << " ";
        currNode = currNode->next;
      }
    }
};

int main()
{
  List list;
  cout << "Insert your list (type 0 to end): ";
  list.input();
  if (list.head == NULL)
  {
    cout << "List is empty" << endl;
  } else
  {
    cout << "List: ";
    list.print();
    cout << endl;
    cout << "is cycle linked list? " << (list.detectCycle() ? "Yes" : "No") << endl;
  }
  return 0;
}
