#pragma once
#include "Player.h"
#include "Board.h"

class RandomPlayer : public Player {
public:
    explicit RandomPlayer(char playerSide);

    void move(Board& board) override;
};
