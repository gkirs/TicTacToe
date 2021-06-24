#include "GameInterface.h"
#include <time.h>
#include <iostream>

int main()
{
    srand(time(0));
    std::cout << "Hi, this is the TicTacToe game!" << std::endl;
    GameInterface gameInterface;
    gameInterface.start();

    return 0;
}
