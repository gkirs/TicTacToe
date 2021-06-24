cmake_minimum_required(VERSION 3.20)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 11)

add_executable(TicTacToe main.cpp Board.cpp Board.h Player.cpp Player.h RandomPlayer.cpp RandomPlayer.h MeatBoxPlayer.cpp MeatBoxPlayer.h SmartPlayer.cpp SmartPlayer.h Game.cpp Game.h GameInterface.cpp GameInterface.h)
