#pragma once

#include "Game.h"
#include "Board.h"
#include <fstream>
#include <iostream>

class GameInterface {
public:
    void start();

private:
    enum GameTypes {
        ONE_GAME,
        SET_OF_GAMES
    };
    struct SetOfGamesResult {
        int n = 0;
        int x_wins = 0;
        int o_wins = 0;
        int draws = 0;

        explicit SetOfGamesResult(int n_games);

        void analyzeGame(bool hasWinner, char winner);
    };

    void playOneGame(Player::PlayerType player1_type, Player::PlayerType player2_type);
    void playSetOfGames(Player::PlayerType player1_type, Player::PlayerType player2_type);

    Player::PlayerType askAboutPlayerType(int player, GameTypes gameType) const;
    GameTypes askAboutGameType() const;
    bool askToPlayAgain(const std::string& question) const;

    void printWinner(char winner) const;
    void printDraw() const;
    void printBoard(const Board& board) const;
    void printSetOfGamesResult(const SetOfGamesResult& set) const;
    void inputBoardToFile(const Board& board, std::ofstream& results) const;
};
