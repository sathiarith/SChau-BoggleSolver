#ifndef TRIE_NODE_H
#define TRIE_NODE_H

#include <string>

class TrieNode {
    private:

    public:
    TrieNode* childNodes[26];  
    bool isWord;
    TrieNode();
    ~TrieNode();

    void insertWord(TrieNode* root, const std::string& word);

};

#endif // TRIE_NODE_H