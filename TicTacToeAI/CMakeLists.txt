# CMakeList.txt : CMake project for TicTacToeAI, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Add source to this project's executable.
add_executable (TicTacToeAI "main.cpp"  "Interface.h" "Player.h" "GUI.h"  "Board.h"  "Settings.h")

# TODO: Add tests and install targets if needed.
