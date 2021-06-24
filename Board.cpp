#include "Board.h"


const std::vector<std::vector<int>> WINNING_ROWS = {    { 0, 1, 2 },
                                                        { 3, 4, 5 },
                                                        { 6, 7, 8 },
                                                        { 0, 3, 6 },
                                                        { 1, 4, 7 },
                                                        { 2, 5, 8 },
                                                        { 0, 4, 8 },
                                                        { 2, 4, 6 } };


Board::Board(){
    board = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
}
bool Board::makeMove(int cell, char c) {
    if(board[cell] == ' '){
        board[cell] = c;
        return true;
    } else return false;
}
const std::vector<char>& Board::getBoard() const {
    return board;
}

char Board::getCell(int cell) const {
    return board[cell];
}