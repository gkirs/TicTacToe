#pragma once
#include "Player.h"
#include "Board.h"

class SmartPlayer : public Player {
public:
    explicit SmartPlayer(char playerSide);

    void move(Board& board) override;

private:
    int predictRowForWin(int x1, int x2, int x3, const Board& board, char c) const;
    int predictWinInNextStep(const Board& board, char c) const;
};
