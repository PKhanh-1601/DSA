//STT: 22520639
//Full Name: Ngô Hoàng Phương Khanh
//Part 2 - Homework 3
//Notes or Remarks:

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <memory>
#include <vector>

using namespace std;

struct HuffmanNode
{
    char ch;
    int freq;
    HuffmanNode *left;
    HuffmanNode *right;

    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct Compare
{
    bool operator()(HuffmanNode *lhs, HuffmanNode *rhs)
    {
        return lhs->freq > rhs->freq;
    }
};

class HuffmanCoding
{
public:
    HuffmanNode *buildHuffmanTree(const unordered_map<char, int> &freqMap)
    {
        priority_queue<HuffmanNode *, vector<HuffmanNode *>, Compare> minHeap;

        for (auto &kv : freqMap)
        {
            HuffmanNode *node = new HuffmanNode(kv.first, kv.second);
            minHeap.push(node);
        }
        if (minHeap.size() == 1)
        {
            HuffmanNode *top = minHeap.top();
            minHeap.pop();
            HuffmanNode *dummy = new HuffmanNode('\0', top->freq);
            dummy->left = top;
            minHeap.push(dummy);
        }
        while (minHeap.size() > 1)
        {
            HuffmanNode *left = minHeap.top();
            minHeap.pop();
            HuffmanNode *right = minHeap.top();
            minHeap.pop();

            HuffmanNode *parent = new HuffmanNode('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;
            minHeap.push(parent);
        }

        return minHeap.top();
    }

    void generateCodes(HuffmanNode *root, const string &prefix)
    {
        if (!root)
            return;
        if (!root->left && !root->right)
        {
            huffmanCodes[root->ch] = prefix;
        }
        generateCodes(root->left, prefix + "0");
        generateCodes(root->right, prefix + "1");
    }

    string encode(const string &text)
    {
        string encodedString;
        for (auto ch : text)
        {
            encodedString += huffmanCodes[ch];
        }
        return encodedString;
    }
    string decode(const string &encodedString, HuffmanNode *root)
    {
        string decodedString;
        HuffmanNode *current = root;
        for (auto bit : encodedString)
        {
            if (bit == '0')
                current = current->left;
            else
                current = current->right;
            if (!current->left && !current->right)
            {
                decodedString.push_back(current->ch);
                current = root;
            }
        }
        return decodedString;
    }

    void compressAndDecompress(const string &text)
    {
        unordered_map<char, int> freqMap;
        for (auto ch : text)
        {
            freqMap[ch]++;
        }
        HuffmanNode *root = buildHuffmanTree(freqMap);
        generateCodes(root, "");
        string encoded = encode(text);
        string decoded = decode(encoded, root);
        cout << "Original Text: " << text << "\n";
        cout << "Huffman Codes:\n";
        for (auto &kv : huffmanCodes)
        {
            cout << kv.first << ": " << kv.second << "\n";
        }
        cout << "Encoded Text: " << encoded << "\n";
        cout << "Decoded Text: " << decoded << "\n";
        freeTree(root);
    }

private:
    unordered_map<char, string> huffmanCodes;

    void freeTree(HuffmanNode *node)
    {
        if (!node)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }
};

int main()
{
    HuffmanCoding huff;
    string text = "hello huffman coding";
    huff.compressAndDecompress(text);
    return 0;
}

