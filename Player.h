#pragma once
#include "Board.h"

class Player {
public:
    enum PlayerType {
        RANDOM_PLAYER,
        SMART_PLAYER,
        MEATBOX_PLAYER
    };
    Player(char playerSide);
    virtual ~Player() = default;

    virtual void move(Board& board) = 0;

    static Player* makeNewPlayer(PlayerType playerType, char playerSide);

    char getPlayerSide() const;

private:
    char playerSide_;
};
