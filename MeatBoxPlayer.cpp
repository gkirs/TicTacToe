#include "MeatBoxPlayer.h"
#include <iostream>

MeatBoxPlayer::MeatBoxPlayer(char playerSide) : Player(playerSide) {};

void MeatBoxPlayer::move(Board& board){
    std::cout << "Your turn! Choose cell 0-8 to make move" << std::endl;
    int cell;
    std::cin >> cell;
    while(!board.makeMove(cell, getPlayerSide())){
        std::cout << "Cell is not empty! Try again!" << std::endl;
        std::cin >> cell;
    }
}

