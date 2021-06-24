#include "SmartPlayer.h"
#include <random>
#include <vector>

int SmartPlayer::predictRowForWin(int x1, int x2, int x3, const Board& board, char c)  const{
    if (board.getCell(x1) == ' ' && board.getCell(x2) == c && board.getCell(x3) == c) return x1;
    else if (board.getCell(x1) == c && board.getCell(x2) == ' ' && board.getCell(x3) == c) return x2;
    else if (board.getCell(x1) == c && board.getCell(x2) == c && board.getCell(x3) == ' ') return x3;
    else return -1;
}

int SmartPlayer::predictWinInNextStep(const Board& board, char c) const{
    int result = -1;
    for (auto row : WINNING_ROWS) {
        result = predictRowForWin(row[0], row[1], row[2], board, c);
        if (result != -1)
            break;
    }
    return result;
}


SmartPlayer::SmartPlayer(char playerSide) : Player(playerSide) {};

void SmartPlayer::move(Board& board){

    // проверяем, можем ли выиграть следующим ходом
    int tmp_WinCell = predictWinInNextStep(board, getPlayerSide());
    if (tmp_WinCell != -1) {
        // если да, то ходим
        board.makeMove(tmp_WinCell, getPlayerSide());
        return;
    }
    // если мы не можем выиграть, тогда проверяем, может ли оппонент выиграть следующим ходом
    int tmp_opponentWinCell;
    if (getPlayerSide() == 'x') {
        tmp_opponentWinCell = predictWinInNextStep(board, 'o');
    }
    else {
        tmp_opponentWinCell = predictWinInNextStep(board, 'x');
    }
    if (tmp_opponentWinCell != -1) {
        // если да, то закрываем ему эту клетку
        board.makeMove(tmp_opponentWinCell, getPlayerSide());
        return;
    }
    // если центр свободен, то приоритетный ход туда, иначе ходим в первый совбодный угол (такое может быть только в начале игры
    // ситуацию с четырьмя занятыми углами я пока не увидел... если углы заняты, то точно уже будет либо защита, либо атака на победу
    // пока отсутствует умение ставить вилки
    if (board.getCell(4) == ' ') {
        board.makeMove(4, getPlayerSide());
        return;
    }
    else {
        // в угол ходить нельзя, когда заняты две противоположных клетки
        // 0) ход ноликов: в угол ходить нельзя, ходим в любую свободную центральную клетку
        //        x|   |
        //       ---------
        //         | o |
        //       ---------
        //         |   | x

        // ход в первый свободный угол не всегда удачен:
        // в двух ситуациях надо перекрыть вилку (пока других не нашел)
        // 1) ход ноликов: ход в правый верхний угол нельзя делать, так как можно получить вилку. ходим в левый нижний угол
        //        x|   |
        //       ---------
        //         | o |
        //       ---------
        //         | x |
        //
        // 2) ход ноликов: ход в левый верхний угол нельзя делать, так как можно получить вилку. ходим в правый нижний угол
        //         |   | x
        //       ---------
        //         | o |
        //       ---------
        //         | x |
        //
        // 3) ход ноликов: ход в левый верхний угол нельзя делать, так как можно получить вилку. ходим в правый нижний угол
        //         |   |
        //       ---------
        //         | o | x
        //       ---------
        //       x |   |
        //
        // 4) ход ноликов: ход в левый верхний угол нельзя делать, так как можно получить вилку. ходим в правый нижний угол
        //         |   |
        //       ---------
        //         | o | x
        //       ---------
        //         | x |
        //
        if((board.getCell(0) == 'x' && board.getCell(4) == 'o' && board.getCell(8) == 'x')
        ||  (board.getCell(2) == 'x' && board.getCell(4) == 'o' && board.getCell(6) == 'x')) {

            std::vector<int> mid_cells = { 1, 3, 5, 7 };
            for (auto mid_cell : mid_cells) {
                if (board.getCell(mid_cell) == ' ') {
                    board.makeMove(mid_cell, getPlayerSide());
                    return;
                }
            }
        }

        if(board.getCell(0) == 'x' && board.getCell(4) == 'o' && board.getCell(7) == 'x' && board.getCell(6) == ' ') {
            board.makeMove(6, getPlayerSide());
            return;
        }
        if(board.getCell(2) == 'x' && board.getCell(4) == 'o' && board.getCell(7) == 'x' && board.getCell(8) == ' ') {
            board.makeMove(8, getPlayerSide());
            return;
        }
        if(board.getCell(5) == 'x' && board.getCell(4) == 'o' && board.getCell(6) == 'x' && board.getCell(8) == ' ') {
            board.makeMove(8, getPlayerSide());
            return;
        }
        if(board.getCell(5) == 'x' && board.getCell(4) == 'o' && board.getCell(7) == 'x' && board.getCell(8) == ' ') {
            board.makeMove(8, getPlayerSide());
            return;
        }
        std::vector<int> corner_cells = { 0, 2, 6, 8 };
        for (auto corner_cell : corner_cells) {
            if (board.getBoard()[corner_cell] == ' ') {
                board.makeMove(corner_cell, getPlayerSide());
                return;
            }
        }
    }

    // если ни куда не походили, ходим в свободную рандомную клетку
    std::vector<int> empty_cells;
    for (size_t i = 0; i < board.getBoard().size(); ++i) {
        if (board.getBoard()[i] == ' ')
            empty_cells.push_back(i);
    }
    int random_cell = rand() % empty_cells.size();

    board.makeMove(empty_cells[random_cell], getPlayerSide());

}

