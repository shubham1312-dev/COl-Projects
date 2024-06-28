#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class TrieNode
{
public:
    unordered_map<char, TrieNode *> children;
    vector<string> suggestions;

    TrieNode() {}
};

class Trie
{
private:
    TrieNode *root;

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char ch : word)
        {
            if (!node->children.count(ch))
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
            node->suggestions.push_back(word);
        }
    }

    vector<string> searchPrefix(const string &prefix)
    {
        TrieNode *node = root;
        vector<string> result;

        for (char ch : prefix)
        {
            if (!node->children.count(ch))
            {
                return result;
            }
            node = node->children[ch];
        }

        return node->suggestions;
    }

public:
    Trie()
    {
        root = new TrieNode();
    }

    void buildTrie(const vector<string> &products)
    {
        for (const string &product : products)
        {
            insert(product);
        }
    }

    vector<string> getSuggestions(const string &query)
    {
        return searchPrefix(query);
    }
};

int main()
{
    vector<string> products = {"mobile", "mouse", "moneypot", "monitor", "mousepad"};
    vector<string> queries = {"m", "mon", "t", "mouse"};

    Trie trie;
    trie.buildTrie(products);

    for (const string &query : queries)
    {
        vector<string> suggestions = trie.getSuggestions(query);
        cout << "For \"" << query << "\": [";
        for (int i = 0; i < suggestions.size(); ++i)
        {
            cout << "\"" << suggestions[i] << "\"";
            if (i < suggestions.size() - 1)
                cout << ", ";
        }
        cout << "]" << endl;
    }

    return 0;
}
