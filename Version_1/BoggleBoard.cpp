#include <random>
#include <iostream>
#include "BoggleBoard.h"

BoggleBoard::BoggleBoard(int size) : size_(size) {
    std::random_device randDev;
    std::default_random_engine randEngine(randDev());
    std::uniform_int_distribution<int> letterGen(65, 90); // ASCII capital letter values
    for (int i = 0; i < size_; i++){
        std::vector<char> row;
        for (int j = 0; j < size_; j++){
            row.push_back(letterGen(randEngine));
        }
        letters.push_back(row);
    }
}

BoggleBoard::~BoggleBoard(){
}

void BoggleBoard::printBoard(){
    for (int i = 0; i < size_; i++){
        for (int j = 0; j < size_; j++){
            std::cout << " " << letters[i][j] << " ";
        }
        std::cout << "\n";
    }
}