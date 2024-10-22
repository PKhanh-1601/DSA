// STT:
// Full Name: Ngô Hoàng Phương Khanh
// Student ID: 22520639
// Homework
// Notes or Remarks: ......

#include <iostream>

using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(NULL) {}
};

class Stack {
public:
    Node* top;
    int size;
    int currentSize;

    Stack(int Size) : top(NULL), size(Size), currentSize(0) {}

    void push(int value) {
        if (isFull()) {
            cout << "Stack is full." << endl;
            return;
        }
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        currentSize++;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;
        } else {
            Node* temp = top;
            int poppedValue = temp->data;
            top = top->next;
            delete temp;
            currentSize--;
            return poppedValue;
        }
    }

    bool isEmpty() {
        return top == NULL;
    }

    bool isFull() {
        return currentSize == size;
    }

    int peek() {
        if (isEmpty()) {
            return -1;
        }
        return top->data;
    }

    void display() {
        Node* runner = top;
        while (runner != NULL) {
            cout << runner->data << " ";
            runner = runner->next;
        }
        cout << endl;
    }
};

void move(Stack &src, Stack &dest, char source, char destination) {
    if (src.isEmpty()) {
        cout << "Move disk " << dest.peek() << " from " << destination << " to " << source << endl;
        src.push(dest.pop());
    } else if (dest.isEmpty()) {
        cout << "Move disk " << src.peek() << " from " << source << " to " << destination << endl;
        dest.push(src.pop());
    } else {
        int pole1TopDisk = src.peek();
        int pole2TopDisk = dest.peek();

        if (pole1TopDisk < pole2TopDisk) {
            cout << "Move disk " << pole1TopDisk << " from " << source << " to " << destination << endl;
            dest.push(src.pop());
        } else {
            cout << "Move disk " << pole2TopDisk << " from " << destination << " to " << source << endl;
            src.push(dest.pop());
        }
    }
}

void printTowers(Stack &src, Stack &tmp, Stack &dest, int disks) {
    cout << "Tower A: ";
    src.display();
    cout << "Tower B: ";
    tmp.display();
    cout << "Tower C: ";
    dest.display();
    cout << endl;
}

void towerOfHanoi(int disks, Stack &src, Stack &tempStack, Stack &dest) {
    char source = 'A', destination = 'C', temp = 'B';

    if (disks % 2 == 0) {
        swap(destination, temp);
    }

    for (int i = disks; i >= 1; i--) {
        src.push(i);
    }

    printTowers(src, tempStack, dest, disks);

    int totalMoves = (1 << disks) - 1;

    for (int i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1) {
            move(src, dest, source, destination);
        } else if (i % 3 == 2) {
            move(src, tempStack, source, temp);
        } else if (i % 3 == 0) {
            move(tempStack, dest, temp, destination);
        }

        printTowers(src, tempStack, dest, disks);
    }
}

void Problem1() {
    cout << "-----Tower of Hanoi-----\n";
    int disks;
    cout << "Enter the number of disks: ";
    cin >> disks;

    Stack src(disks);
    Stack tempStack(disks);
    Stack dest(disks);

    towerOfHanoi(disks, src, tempStack, dest);
}

struct BrowserNode {
    string data;
    BrowserNode* next;

    BrowserNode(string value) : data(value), next(NULL) {}
};

class BrowserStack {
public:
    BrowserNode* top;

    BrowserStack() : top(NULL) {}

    void push(string data) {
        BrowserNode* newBrowserNode = new BrowserNode(data);
        newBrowserNode->next = top;
        top = newBrowserNode;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Empty Browser history" << endl;
            return;
        }

        BrowserNode* temp = top;
        top = top->next;
        delete temp;
    }

    string peek() {
        if (isEmpty()) {
            cout << "Empty Browser history" << endl;
            return "";
        }
        return top->data;
    }

    bool isEmpty() {
        return (top == NULL);
    }

    ~BrowserStack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

class Browser {
private:
    BrowserStack backStack;
    BrowserStack forwardStack;

public:
    void visit(string url) {
        if (!backStack.isEmpty()) {
            while (!forwardStack.isEmpty()) {
                forwardStack.pop();
            }
        }
        backStack.push(url);
    }

    string back() {
        if (backStack.isEmpty()) {
            return "There is no URL in history to go back.";
        }

        string currentSite = backStack.peek();
        forwardStack.push(currentSite);
        backStack.pop();

        if (backStack.isEmpty()) {
            return "There is no URL in history to go back.";
        } else {
            return backStack.peek();
        }
    }

    string forward() {
        if (forwardStack.isEmpty()) {
            return "There is no URL to go forward.";
        }

        string siteToGoForward = forwardStack.peek();
        backStack.push(siteToGoForward);
        forwardStack.pop();
        return backStack.peek();
    }
};

void printBrowserNavigation() {
    cout << "-------------------------------\n"
         << "Browser history navigation:\n"
         << "1 - Visit a new URL\n"
         << "2 - Go back to the previous URL\n"
         << "3 - Go forward to the next URL\n"
         << "4 - Exit\n"
         << "-------------------------------\n";
}

void Problem2() {
    Browser browser;
    while (true) {
        printBrowserNavigation();
        cout << "Enter your choice: ";
        int option;
        cin >> option;
        string URL;

        switch (option) {
        case 1:
            cout << "Enter a URL to visit: ";
            cin >> URL;
            browser.visit(URL);
            break;
        case 2:
            cout << "Current URL: " << browser.back() << endl;
            break;
        case 3:
            cout << "Current URL: " << browser.forward() << endl;
            break;
        case 4:
            cout << "Exiting...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}

void visible(int heights[], int n, int visibleCounts[]) {
    Stack heightStack(n);

    for (int i = n - 1; i >= 0; i--) {
        int count = 0;
        int currentHeight = heights[i];

        while (!heightStack.isEmpty() && heightStack.peek() < currentHeight) {
            heightStack.pop();
            count++;
        }

        if (!heightStack.isEmpty() && heightStack.peek() >= currentHeight) {
            count++;
        }

        visibleCounts[i] = count;
        heightStack.push(currentHeight);
    }
}

void Problem3() {
    cout << "Enter the amount of people in the queue: ";
    int people;
    cin >> people;

    int heights[100];
    int visibleCounts[100];

    cout << "Enter height for each one:\n";
    for (int i = 0; i < people; i++) {
        cin >> heights[i];
    }

    visible(heights, people, visibleCounts);

    cout << "Visible counts: ";
    for (int i = 0; i < people; i++) {
        cout << visibleCounts[i] << " ";
    }
    cout << endl;
}

struct Fruit {
    int id;
    int price;
    Fruit* nextFruit;
    Fruit(int ID, int coin) : id(ID), price(coin), nextFruit(NULL) {}
};

class FruitQueue {
public:
    Fruit* front;
    Fruit* rear;
    int totalCoins;
    int nextFreeIndex;

    FruitQueue() : front(NULL), rear(NULL), totalCoins(0), nextFreeIndex(0) {}

    void addFruit(int id, int price) {
        Fruit* newFruit = new Fruit(id, price);
        if (rear == NULL) {
            front = rear = newFruit;
        } else {
            rear->nextFruit = newFruit;
            rear = newFruit;
        }
    }

    void removeFruit() {
        if (front == NULL) {
            return;
        }
        Fruit* temp = front;
        front = front->nextFruit;
        if (front == NULL) {
            rear = NULL;
        }
        delete temp;
    }

    void buyFruit() {
        nextFreeIndex = front->id + 1;
        totalCoins += front->price;
        removeFruit();
    }

    void skipFruit() {
        nextFreeIndex--;
        removeFruit();
    }

    int findNextFruitToBuy() {
        if (nextFreeIndex == 0 || front == NULL) {
            return front->id;
        }
        int tempFree = nextFreeIndex;
        int buyId = front->id;
        int bestPrice = front->price;
        Fruit* runner = front->nextFruit;

        while (runner != NULL && tempFree > 0) {
            if (runner->price < bestPrice) {
                bestPrice = runner->price;
                buyId = runner->id;
            }
            runner = runner->nextFruit;
            tempFree--;
        }
        if (tempFree > 0) {
            return -1;
        }
        return buyId;
    }

    int calculateMinCoins() {
        while (front != NULL) {
            int buyId = findNextFruitToBuy();
            if (buyId == -1) {
                break;
            }
            if (front->id == buyId) {
                buyFruit();
            } else {
                skipFruit();
            }
        }
        return totalCoins;
    }
};

void Problem4() {
    FruitQueue fruitQueue;
    int n;
    cout << "Enter the amount of fruit: ";
    cin >> n;
    int price;
    cout << "Enter price for each fruit:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Fruit " << i + 1 << ": ";
        cin >> price;
        fruitQueue.addFruit(i, price);
    }

    cout << "Minimum cost: " << fruitQueue.calculateMinCoins() << endl;
}

int main()
{
    cout << "Select a problem to run (1-4): ";
    int option;
    cin >> option;

    switch (option)
    {
    case 1:
        Problem1();
        break;
    case 2:
        Problem2();
        break;
    case 3:
        Problem3();
        break;
    case 4:
        Problem4();
        break;
    default:
        break;
    }
    return 0;
}
