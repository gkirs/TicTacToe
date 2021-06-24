#pragma once
#include <vector>
#include "Board.h"
#include "Player.h"


class Game {
public:
    Game(Player::PlayerType player1_type, Player::PlayerType player2_type);
    ~Game();

    const Board& getBoard() const;

    //void start();
    void nextMove();
    void allMoves();

    bool isGameHasWinner() const;
    char getWinner() const;
    bool isGameFinished() const;

private:
    enum playersMovesSequence {
        Player_1_Move,
        Player_2_Move
    };
    playersMovesSequence whichPlayerMove = Player_1_Move;
    Board board;
    Player *player1 = nullptr;
    Player *player2 = nullptr;
    int movesCount = 0;
    bool hasWinner = false;
    char winner = ' ';
    bool gameFinished = false;

    bool checkRowForWin(const std::vector<int>& row);
    char findWinner();
};
