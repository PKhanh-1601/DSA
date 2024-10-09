//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Session 01 - Homework
//Notes or Remarks:

#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int stringToInt(const string& str) {
    int num;
    stringstream ss(str);
    ss >> num;
    return num;
}

// Homework 1
struct Song
{
    string nameSong;
    Song *nextSong;
    Song *prevSong;
    Song(string s)
    {
        nameSong = s;
        nextSong = NULL;
        prevSong = NULL;
    }
};

struct PlayList
{
    Song *firstSong;
    Song *lastSong;
    Song *currentSong;
    PlayList()
    {
        firstSong = NULL;
        lastSong = NULL;
        currentSong = NULL;
    }

    void ADD(string s)
    {
        Song *newsong = new Song(s);
        if (firstSong == NULL)
        {
            firstSong = lastSong = newsong;
            lastSong->nextSong = firstSong;
            firstSong->nextSong = lastSong;
        }
        else
        {
            lastSong->nextSong = newsong;
            newsong->prevSong = lastSong;
            newsong->nextSong = firstSong;
            firstSong->prevSong = newsong;
            lastSong = newsong;
        }
        currentSong = firstSong;
    }

    void REMOVE(string s)
    {
        if (firstSong == NULL) return;
        Song *tmp = firstSong;
        do {
            if (tmp->nameSong == s)
            {
                if (tmp == firstSong)
                {
                    if (firstSong == lastSong)
                    {
                        delete firstSong;
                        firstSong = lastSong = NULL;
                        currentSong = NULL;
                    }
                    else
                    {
                        firstSong = firstSong->nextSong;
                        firstSong->prevSong = lastSong;
                        lastSong->nextSong = firstSong;
                        delete tmp;
                        currentSong = firstSong;
                    }
                }
                else if (tmp == lastSong)
                {
                    lastSong = lastSong->prevSong;
                    lastSong->nextSong = firstSong;
                    firstSong->prevSong = lastSong;
                    delete tmp;
                    currentSong = firstSong;
                }
                else
                {
                    tmp->prevSong->nextSong = tmp->nextSong;
                    tmp->nextSong->prevSong = tmp->prevSong;
                    delete tmp;
                }
                return;
            }
            tmp = tmp->nextSong;
        } while (tmp != NULL);
    }

    void NEXT()
    {
        if (firstSong != NULL)
            firstSong = firstSong->nextSong;
    }

    void PREV()
    {
        if (firstSong != NULL)
            firstSong = firstSong->prevSong;
    }

    void DISPLAY()
    {
        if (firstSong == NULL) return;
        Song *CurrSong = firstSong;
        do
        {
            cout << CurrSong->nameSong << " ";
            CurrSong = CurrSong->nextSong;
        } while (CurrSong != firstSong);
        cout << endl;
    }
};

void MusicPlayer()
{
    PlayList music;
    int op;
    cout << "Enter number of operations: ";
    cin >> op;
    string operation;
    cout << "Enter your operations: " << endl;
    for (int i = 0; i < op; i++)
    {
        cin >> operation;
        if (operation == "ADD")
        {
            string nameSong;
            cin >> nameSong;
            music.ADD(nameSong);
        }
        else if (operation == "NEXT")
        {
            music.NEXT();
        }
        else if (operation == "PREV")
        {
            music.PREV();
        }
        else if (operation == "DISPLAY")
        {
            music.DISPLAY();
        }
        else if (operation == "REMOVE")
        {
            string removeName;
            cin >> removeName;
            music.REMOVE(removeName);
        }
    }
}

// Homework 2
struct Tab
{
    string URL;
    Tab *prevTab;
    Tab *nextTab;
    Tab(string webpage)
    {
        URL = webpage;
        prevTab = NULL;
        nextTab = NULL;
    }
};

struct BrowserHistory
{
    Tab *firstTab;
    Tab *lastTab;
    Tab *currentTab;
    BrowserHistory(string webpage)
    {
        Tab *initTab = new Tab(webpage);
        firstTab = lastTab = currentTab = initTab;
    }

    void VisitURLS(string webpage)
    {
        Tab *newPage = new Tab(webpage);
        if (currentTab != lastTab)
        {
            currentTab->nextTab = NULL;
            lastTab = currentTab;
        }
        lastTab->nextTab = newPage;
        newPage->prevTab = lastTab;
        lastTab = newPage;
        currentTab = newPage;
    }

    void backWeb(int steps)
    {
        for (int i = 0; i < steps; i++)
        {
            if (currentTab->prevTab == NULL) break;
            else currentTab = currentTab->prevTab;
        }
    }

    void forwardWeb(int steps)
    {
        for (int i = 0; i < steps; i++)
        {
            if (currentTab->nextTab == NULL) break;
            else currentTab = currentTab->nextTab;
        }
    }

    void showTab()
    {
        cout << currentTab->URL << " ";
    }
};

void WebBrowser()
{
    vector<string> command;
    vector<string> webpage;
    string input;
    cout << "Input your commands (type 'done' when finished):\n";
    while (true)
    {
        cin >> input;
        if (input == "done") break;
        command.push_back(input);
    }

    cout << "Input URLs and steps (type 'done' when finished):\n";
    while (true)
    {
        cin >> input;
        if (input == "done") break;
        webpage.push_back(input);
    }

    BrowserHistory history(webpage[0]);
    cout << "null ";
    for (int i = 1; i < command.size(); i++)
    {
        if (command[i] == "visit")
        {
            history.VisitURLS(webpage[i]);
            cout << "null ";
        }
        else if (command[i] == "back")
        {
            int steps = stringToInt(webpage[i]);  // Sử dụng stringToInt thay cho stoi
            history.backWeb(steps);
            history.showTab();
        }
        else if (command[i] == "forward")
        {
            int steps = stringToInt(webpage[i]);  // Sử dụng stringToInt thay cho stoi
            history.forwardWeb(steps);
            history.showTab();
        }
    }
}

// Homework 3
struct Token
{
    string TokenID;
    int ExpirationTime;
    Token *next;
    Token(string tokenID, int expTime)
    {
        TokenID = tokenID;
        ExpirationTime = expTime;
        next = NULL;
    }
};

struct AuthenticationManager
{
    int TimeToLive;
    Token *head;
    AuthenticationManager(int ttl)
    {
        TimeToLive = ttl;
        head = NULL;
    }

    void generateToken(string tokenID, int currentTime)
    {
        int expTime = currentTime + TimeToLive;
        Token *newToken = new Token(tokenID, expTime);
        newToken->next = head;
        head = newToken;
    }

    void renew(string tokenID, int currentTime)
    {
        Token *curr = head;
        while (curr != NULL)
        {
            if (curr->TokenID == tokenID && curr->ExpirationTime > currentTime)
            {
                curr->ExpirationTime = currentTime + TimeToLive;
                return;
            }
            curr = curr->next;
        }
    }

    int countUnexpiredTokens(int currentTime)
    {
        int countnum = 0;
        Token *curr = head;
        while (curr != NULL)
        {
            if (curr->ExpirationTime > currentTime)
            {
                countnum++;
            }
            curr = curr->next;
        }
        return countnum;
    }
};

void Authentication()
{
    vector<string> command;
    string input;
    cout << "Input your commands (type 'done' when finished):\n";

    while (true)
    {
        cin >> input;
        if (input == "done") break;
        command.push_back(input);
    }

    AuthenticationManager *authManager = NULL;

    for (int i = 0; i < command.size(); i++)
    {
        if (command[i] == "AuthenticationManager")
        {
            int TimeToLive;
            cin >> TimeToLive;
            authManager = new AuthenticationManager(TimeToLive);
            cout << "null ";
        }
        else if (command[i] == "generate" || command[i] == "renew")
        {
            string tokenID;
            int currentTime;
            cin >> tokenID >> currentTime;
            if (command[i] == "generate")
            {
                authManager->generateToken(tokenID, currentTime);
                cout << "null ";
            }
            else
            {
                authManager->renew(tokenID, currentTime);
                cout << "null ";
            }
        }
        else if (command[i] == "countUnexpiredTokens")
        {
            int currentTime;
            cin >> currentTime;
            int countnum = authManager->countUnexpiredTokens(currentTime);
            cout << countnum << " ";
        }
    }
}

void menu()
{
    cout << "Enter your choice: " << endl;
    cout << "1. Homework 1" << endl;
    cout << "2. Homework 2" << endl;
    cout << "3. Homework 3" << endl;
    int input;
    cin >> input;
    switch (input)
    {
    case 1:
        MusicPlayer();
        break;
    case 2:
        WebBrowser();
        break;
    case 3:
        Authentication();
        break;
    }
}

int main()
{
    menu();
}
