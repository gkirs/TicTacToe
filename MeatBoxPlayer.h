#pragma once
#include "Player.h"
#include "Board.h"

class MeatBoxPlayer : public Player {
public:
    explicit MeatBoxPlayer(char playerSide);

    void move(Board& board) override;
};

