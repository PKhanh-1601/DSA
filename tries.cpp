//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 9
//Notes or Remarks:

#include <iostream>
#include <unordered_map>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string& prefix) {
        TrieNode* node = root;
        for (char ch : prefix) {
            if (node->children.find(ch) == node->children.end()) {
                return false;
            }
            node = node->children[ch];
        }
        return true;
    }

    void printAllWords(TrieNode* node, string word) {
        if (node->isEndOfWord) {
            cout << word << endl;
        }
        for (auto it : node->children) {
            printAllWords(it.second, word + it.first);
        }
    }

    void printAllWords() {
        printAllWords(root, "");
    }
};

int main() {
    Trie trie;
    trie.insert("apple");
    trie.insert("app");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bandana");

    cout << "Search for 'apple': " << (trie.search("apple") ? "Found" : "Not Found") << endl;
    cout << "Search for 'app': " << (trie.search("app") ? "Found" : "Not Found") << endl;
    cout << "Search for 'ban': " << (trie.search("ban") ? "Found" : "Not Found") << endl;
    cout << "Starts with 'ban': " << (trie.startsWith("ban") ? "Yes" : "No") << endl;
    cout << "Starts with 'band': " << (trie.startsWith("band") ? "Yes" : "No") << endl;

    cout << "All words in the Trie:" << endl;
    trie.printAllWords();

    return 0;
}
