#pragma once
#include <vector>

extern const std::vector<std::vector<int>> WINNING_ROWS;

class Board {
public:

    Board();

    const std::vector<char>& getBoard() const;
    bool makeMove(int cell, char c);
    char getCell(int cell) const;

private:
    std::vector<char> board;
};