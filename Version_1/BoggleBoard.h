#ifndef BOGGLE_BOARD_H
#define BOGGLE_BOARD_H

#include <vector>

/**
 * @brief Game board that stores characters.
 * 
 * @param size size*size dimension
 */
class BoggleBoard {
    private:
    int size_;
    
    public:
    std::vector<std::vector<char>> letters;
    
    BoggleBoard(int size);
    ~BoggleBoard();

    void printBoard();
    
};

#endif // BOGGLE_BOARD_H