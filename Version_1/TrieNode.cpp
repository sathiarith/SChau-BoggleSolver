#include "TrieNode.h"

TrieNode::TrieNode(){ 
    for (int i = 0; i < 26; ++i)  
        childNodes[i] = nullptr;  
    isWord = false;  
}
TrieNode::~TrieNode(){}

void TrieNode::insertWord(TrieNode* root, const std::string& word){
    TrieNode* curr = root;  
    for (char letter : word) {  
        int index = toupper(letter) - 'A';  // A - A is the first letter/child  
        if (curr->childNodes[index] == nullptr)  
            curr->childNodes[index] = new TrieNode();  
        curr = curr->childNodes[index];  
    }  
    curr->isWord = true; 
}