#include "GameInterface.h"
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>

void GameInterface::start(){
    bool freshStart = true;
    while (freshStart) {
        GameTypes gameType = askAboutGameType();

        Player::PlayerType player1_type = askAboutPlayerType(1,gameType);
        Player::PlayerType player2_type = askAboutPlayerType(2,gameType);

        if(gameType == ONE_GAME){
            bool repeatThisGame = true;
            while (repeatThisGame){
                playOneGame(player1_type, player2_type);
                repeatThisGame = askToPlayAgain("Repeat this game?");
            }
        } else if (gameType == SET_OF_GAMES){
            playSetOfGames(player1_type, player2_type);
        }

        freshStart = askToPlayAgain("Restart program?");
    }
}

void GameInterface::playOneGame(Player::PlayerType player1_type, Player::PlayerType player2_type){
    Game game(player1_type, player2_type);
    printBoard(game.getBoard());
    while (!game.isGameFinished()) {
        Sleep(1000);
        game.nextMove();
        printBoard(game.getBoard());
    }
    printBoard(game.getBoard());
    if (game.isGameHasWinner())
        printWinner(game.getWinner());
    else
        printDraw();
}

void GameInterface::playSetOfGames(Player::PlayerType player1_type, Player::PlayerType player2_type){
    std::cout << "How many games to play?" << std::endl;
    int n_games;
    std::string n_games_string;
    while (true) {
        std::cin >> n_games_string;
        try {
            n_games = std::stoi(n_games_string);
        }  catch (const std::invalid_argument &e) {
            std::cout << "Invalid value, enter again:" << std::endl;
            continue;
        }
        if(n_games > 0){
            break;
        } else {
            std::cout << "Number of games cant be under zero! Enter again:" << std::endl;
        }
    }

    SetOfGamesResult setOfGamesResult(n_games);
    std::ofstream results;
    results.open("TicTacToe_results.csv");
    for (int i = 0; i < setOfGamesResult.n; i++){
        Game game(player1_type, player2_type);
        game.allMoves();
        setOfGamesResult.analyzeGame(game.isGameHasWinner(), game.getWinner());
        inputBoardToFile(game.getBoard(), results);
        results << std::endl;
    }
    printSetOfGamesResult(setOfGamesResult);
    results.close();
}

GameInterface::GameTypes GameInterface::askAboutGameType() const{
    std::cout << "What type of game do you want?" << std::endl
    << "1 - one game (you also can play)" << std::endl
    << "2 - set of n games between computer, it will save results to file" << std::endl
    << "Choose your game:" << std::endl;

    std::string gameType;
    while(true){
        std::cin >> gameType;
        if(gameType == "1")
            return ONE_GAME;
        if(gameType == "2")
            return SET_OF_GAMES;
        std::cout << "Invalid value, enter again:" << std::endl;
    }
}

Player::PlayerType GameInterface::askAboutPlayerType(int player, GameTypes gameType) const{
    std::cout << "Player " << player << ": who will play?" << std::endl
    << "R - random computer play" << std::endl
    << "S - smart computer play" << std::endl
    << (gameType == ONE_GAME ? "H - human play\n" : "")
    << "Type your answer:" << std::endl;

    std::string playerType;
    while(true) {
        std::cin >> playerType;
        if (playerType == "R")
            return Player::RANDOM_PLAYER;
        if(playerType == "S")
            return Player::SMART_PLAYER;
        if(playerType == "H" && gameType == ONE_GAME)
            return Player::MEATBOX_PLAYER;
        std::cout << "Invalid value, enter again:" << std::endl;
    }
}

bool GameInterface::askToPlayAgain(const std::string& question) const{
    std::cout << question << std::endl
    << "Type 'yes' or 'no': " << std::endl;
    std::string answer;
    while (true) {
        std::cin >> answer;
        if(answer == "yes"){
            system("cls");
            return true;
        }
        if(answer == "no")
            return false;

        std::cout << "Invalid answer, enter again: " << std::endl;
    }
}

void GameInterface::printWinner(char winner) const{
    std::cout << '\t' << winner << " won the game!" << std::endl;
}

void GameInterface::printDraw() const{
    std::cout << "This time it's a draw" << std::endl;
}

void GameInterface::printBoard(const Board& board) const{
    system("cls");
    std::cout << "\n\t" << board.getCell(0)<< " | " << board.getCell(1) << " | " << board.getCell(2);
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board.getCell(3) << " | " << board.getCell(4) << " | " << board.getCell(5);
    std::cout << "\n\t" << "---------";
    std::cout << "\n\t" << board.getCell(6) << " | " << board.getCell(7) << " | " << board.getCell(8);
    std::cout << "\n\n";
}

void GameInterface::printSetOfGamesResult(const SetOfGamesResult& set) const{
    std::cout << "Games played:" << '\t' << set.n << std::endl;
    std::cout << "x wins:" << '\t' << set.x_wins << std::endl;
    std::cout << "o wins:" << '\t' << set.o_wins << std::endl;
    std::cout << "draws:" << '\t' << set.draws << std::endl;
}

void GameInterface::inputBoardToFile(const Board& board, std::ofstream& results) const{
    results << board.getCell(0);
    for(size_t i = 1; i < board.getBoard().size(); ++i){
        results  << ',' <<board.getCell(i);
    }
}

void GameInterface::SetOfGamesResult::analyzeGame(bool hasWinner, char winner)  {
    if(hasWinner){
        if(winner == 'x')
            x_wins++;
        if(winner == 'o')
            o_wins++;
    } else
        draws++;
}

GameInterface::SetOfGamesResult::SetOfGamesResult(int n_games) {
    n = n_games;
}
