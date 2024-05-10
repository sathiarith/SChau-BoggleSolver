#include <iostream>  
#include <vector>  
#include <string>  
#include <algorithm>
#include <fstream>
#include "BoggleBoard.h"
#include "TrieNode.h"  

/*
Boggle Solver Program by Sathiarith Chau

Given a randomly generated Boggle configuration of alphabet letters,
all possible strings will be generated and compared to a dictionary
in order to populate a list of all words.

*/

// prepocessor directives to choose which container to use
#define DICTIONARY_TRIE
//#define DICTIONARY_VEC

const int SIZE = 4;  // Assuming a 4x4 grid, modify as per your requirements    
int vecWordCount = 0; // word count for brute force search

/**
 * @brief Function to perform depth-first search (DFS) using dictionary trie.
 * 
 * @param board 
 * @param node 
 * @param row 
 * @param col 
 * @param visited 
 * @param currentWord 
 * @param foundWords 
 * @return * void 
 */
void dfs_using_trie(const std::vector<std::vector<char>>& board, TrieNode* node, int row, int col, std::vector<std::vector<bool>>& visited, std::string& currentWord, std::vector<std::string>& foundWords) {  
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || visited[row][col])  
        return;  
  
    char letter = board[row][col];
    // Position of letter in alphabet order corresponding to array index of size 26
    // (e.g., A - A or 65 - 65 == 0th alphabet being A)
    int index = letter - 'A';  // Letter is ensured uppercase letters  
  
    if (node->childNodes[index] == nullptr)  
        return;  
  
    visited[row][col] = true;  
    currentWord += letter;  
  
    if (node->childNodes[index]->isWord) {  
        foundWords.push_back(currentWord);  
        node->childNodes[index]->isWord = false;  // Mark found to exclude word repeats 
    }  
  
    // Neighbor positions/coordinates
    // order: 0. bottom-left, 1. left, 2) upper-left, 3. bottom, 4. up, 5. bottom-right, 6) right, 7. upper-right
    static int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};  
    static int colOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  
    for (int i = 0; i < 8; ++i){
        dfs_using_trie(board, node->childNodes[index], row + rowOffsets[i], col + colOffsets[i], visited, currentWord, foundWords);
    }

    // Reset for the next word search in new position on board
    currentWord.pop_back();  
    visited[row][col] = false;  
}

/**
 * @brief Function to perform depth-first search (DFS) using dictionary as vector<string>.
 * Written for the purpose of demonstration, impractical to above size 3.
 * 
 * @param board 
 * @param vec 
 * @param row 
 * @param col 
 * @param visited 
 * @param currentWord 
 * @param foundWords 
 */
void dfs_using_vec(const std::vector<std::vector<char>>& board, std::vector<std::string>& vec, int row, int col, 
                    std::vector<std::vector<bool>>& visited, std::string& currentWord, std::vector<std::string>& foundWords) {  
    if (row < 0 || row >= SIZE || col < 0 || col >= SIZE || visited[row][col])  
        return;  
  
    char letter = board[row][col]; 
  
    visited[row][col] = true;  
    currentWord += letter;
    for (auto word:vec){
        if (word == currentWord){
            foundWords.push_back(currentWord);
        }
    }

  
    // Neighbor positions/coordinates
    // order: 0. bottom-left, 1. left, 2. upper-left, 3. bottom, 4. up, 5. bottom-right, 6. right, 7. upper-right
    static int rowOffsets[] = {-1, -1, -1, 0, 0, 1, 1, 1};  
    static int colOffsets[] = {-1, 0, 1, -1, 1, -1, 0, 1};

  
    for (int i = 0; i < 8; ++i) {
        dfs_using_vec(board, vec, row + rowOffsets[i], col + colOffsets[i], visited, currentWord, foundWords); 
    } 
  
    // Reset for the next word search in new position on board
    vecWordCount++;
    std::cout << row << " " << col << " " << currentWord << " " << vecWordCount << "\n";
    
    currentWord.pop_back();  
    visited[row][col] = false;   
    
}
  
/**
 * @brief Function to find all possible words in the Boggle board 
 * 
 * @param board 
 * @param root 
 * @param dictionary 
 * @return * std::vector<std::string> 
 */
std::vector<std::string> findWords(const std::vector<std::vector<char>>& board, TrieNode* root, std::vector<std::string>& dictionary) {  
    std::vector<std::vector<bool>> visited(SIZE, std::vector<bool>(SIZE, false));  
    std::vector<std::string> foundWords;  
    std::string currentWord = "";  

    #if defined(DICTIONARY_TRIE)
    for (int row = 0; row < SIZE; ++row) {  
        for (int col = 0; col < SIZE; ++col) {  
            dfs_using_trie(board, root, row, col, visited, currentWord, foundWords);  
        }  
    }
    #elif defined(DICTIONARY_VEC)
    for (int row = 0; row < SIZE; ++row) {  
        for (int col = 0; col < SIZE; ++col) {  
            dfs_using_vec(board, dictionary, row, col, visited, currentWord, foundWords);  
        }  
    }
    #endif
    return foundWords;  
}  

/**
 * @brief Initialize dictionary trie from text file.
 * 
 * @param trie 
 */
void makeDictionaryTrie(TrieNode* trie){
    std::fstream dictFile;
    dictFile.open("../BoggleSolver/dictionary_178k_w.txt", std::ios::in); 
    if (dictFile.is_open()){
        std::string word;
        getline(dictFile, word);
        while(getline(dictFile, word)){
            trie->insertWord(trie, word);
        }
        dictFile.close();
    }
    else {
        std::cout << "No word file found.\n"; 
    }
}

/**
 * @brief Initialize dictionary vector of strings from text file.
 * 
 * @param vector 
 */
void makeDictionaryVec(std::vector<std::string>& vector){
    std::fstream dictFile;
    dictFile.open("../BoggleSolver/dictionary_178k_w.txt", std::ios::in); 
    if (dictFile.is_open()){
        std::string word;
        getline(dictFile, word);
        while(getline(dictFile, word)){
            vector.push_back(word);
        }
        dictFile.close();
    }
    else {
        std::cout << "No word file found.\n"; 
    }
}

int main() {  
    TrieNode* dictionaryTrie = new TrieNode();
    std::vector<std::string> dictionaryVec;
    BoggleBoard board(SIZE); 
  
    // Create the different data structure
    makeDictionaryTrie(dictionaryTrie);
    makeDictionaryVec(dictionaryVec);
    
    std::vector<std::string> foundWords = findWords(board.letters, dictionaryTrie, dictionaryVec);  

    std::cout << "Found Words:\n";  
    for (const std::string& word : foundWords)
        if (word.size() >= 3){
            std::cout << word << "\n";
        }
    
    board.printBoard();

    return 0;
}