#include "Game.h"
#include <vector>

Game::Game(Player::PlayerType player1_type, Player::PlayerType player2_type) {
    player1 = Player::makeNewPlayer(player1_type, 'x');
    player2 = Player::makeNewPlayer(player2_type, 'o');
}

Game::~Game(){
    delete player1;
    delete player2;
}

//void Game::start() {
//}

void Game::nextMove() {
    whichPlayerMove == Player_1_Move ? player1->move(board):player2->move(board);
    whichPlayerMove == Player_1_Move ? whichPlayerMove = Player_2_Move:whichPlayerMove = Player_1_Move;
    movesCount++;
    winner = findWinner();
    if(movesCount == 9 || hasWinner)
        gameFinished = true;
}

void Game::allMoves(){
    while(!gameFinished) nextMove();
}

bool Game::isGameHasWinner() const{
    return hasWinner;
}

char Game::getWinner() const{
    return winner;
}

const Board& Game::getBoard() const{
    return board;
}

bool Game::isGameFinished() const{
    return gameFinished;
}

bool Game::checkRowForWin(const std::vector<int>& row) {
    if (board.getCell(row[0]) != ' ' && board.getCell(row[0]) == board.getCell(row[1]) && board.getCell(row[0]) == board.getCell(row[2]))
        return true;
    else
        return false;
}

char Game::findWinner() {
    char winner = ' ';
    for (auto row : WINNING_ROWS) {
        if (checkRowForWin(row)) {
            hasWinner = true;
            winner = board.getCell(row[0]);
            break;
        }
    }
    return winner;
}

