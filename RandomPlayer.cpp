#include "RandomPlayer.h"
#include <random>
#include <vector>

RandomPlayer::RandomPlayer(char playerSide) : Player(playerSide) {};

void RandomPlayer::move(Board& board){
    std::vector<int> empty_cells;
    for (size_t i = 0; i < board.getBoard().size(); ++i) {
        if (board.getCell(i) == ' ')
            empty_cells.push_back(i);
    }
    int random_cell = rand() % empty_cells.size();

    board.makeMove(empty_cells[random_cell], getPlayerSide());
}

