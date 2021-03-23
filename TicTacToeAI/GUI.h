#include "Player.h"
#include <iostream>
#include <string>
#include <fstream>

class GUI {
public:
	std::string print(Board & board);
    int menu(bool & gamePlayed);
    void saveBoard(std::vector<Move> & replay);
    void replayBoard(std::vector<Move>& replay);
    void settings();

    void processedCount(int board_count) { std::cout << std::endl << board_count << " Boards were processed in that last game." << std::endl;  }
};

std::string GUI::print(Board & board)
{
    std::string _tempstr;
    char __state;
    _tempstr = "\n  ";
    for (int x_line = 0; x_line < gameSettings.getBoardSize(); x_line++)
    {
        _tempstr += std::to_string(x_line + 1);
        _tempstr += " ";
    }
    _tempstr += "\n";
    for (int y = 0; y < gameSettings.getBoardSize(); y++)
    {
        _tempstr += std::to_string(y + 1);
        _tempstr += " ";
        for (int x = 0; x < gameSettings.getBoardSize(); x++)
        {
            __state = board.getState(x, y);
            if (__state == gameSettings.getXVal()) {
                _tempstr += COLOR_BLUE;
                _tempstr += __state;
                _tempstr += " ";
            }
            else if (__state == gameSettings.getOVal()) {
                _tempstr += COLOR_RED;
                _tempstr += __state;
                _tempstr += " ";
            }
            else {
                _tempstr += COLOR_RESET;
                _tempstr += __state;
                _tempstr += " ";
            }

        }
        _tempstr += COLOR_RESET;
        _tempstr += "\n";
    }
    return _tempstr;
}

int GUI::menu(bool & gamePlayed) {
    int response;
    std::cout << "Would you like to play against an AI or do you wish to watch a game?" << std::endl;
    std::cout << "1. Play Against an AI" << std::endl;
    std::cout << "2. Watch AI vs AI" << std::endl;
    if (gamePlayed)
    {
        std::cout << "3. Save Last Game" << std::endl;
        std::cout << "4. Replay Last Game" << std::endl;
        std::cout << "5. Boards Processed in Last Game" << std::endl;
    }
    std::cout << "6. Settings" << std::endl;
    std::cout << "7. Exit" << std::endl;
    std::cin >> response;
    return response;
}

void GUI::saveBoard(std::vector<Move> & replay) {
    Board board;
    GUI gui;
    std::ofstream print("last_game.txt");
    for (int i = 0; i < replay.size(); i++)
    {
        board.addState(replay[i].x, replay[i].y, gameSettings.getXVal());
        print << gui.print(board);
        i++;
        if (i < replay.size()) {
            board.addState(replay[i].x, replay[i].y, gameSettings.getOVal());
            print << gui.print(board);
        }
    }
    char winner = board.isVict();
    if (winner == gameSettings.getXVal() || winner == gameSettings.getOVal())
    {
        print << "The winner is: " << winner << std::endl;
    }
    else
    {
        print << "The game is a tie!" << std::endl;
    }
    print.close();
}
void GUI::replayBoard(std::vector<Move>& replay) {
    Board board;
    GUI gui;
    for (int i = 0; i < replay.size(); i++)
    {
        board.addState(replay[i].x, replay[i].y, gameSettings.getXVal());
        std::cout << gui.print(board);
        i++;
        if (i < replay.size()) {
            board.addState(replay[i].x, replay[i].y, gameSettings.getOVal());
            std::cout << gui.print(board);
        }
    }
    char winner = board.isVict();
    if (winner == gameSettings.getXVal() || winner == gameSettings.getOVal())
    {
        std::cout << "The winner is: " << winner << std::endl;
    }
    else
    {
        std::cout << "The game is a tie!" << std::endl;
    }
}

void GUI::settings() {
    char tempchar;
    int tempint;
    std::cout << "Blank Value: (Currently - " << gameSettings.getBlankVal() << ")" << std::endl;
    std::cin >> tempchar;
    gameSettings.setBlankVal(tempchar);
    std::cout << "O Value: (Currently - " << gameSettings.getOVal() << ")" << std::endl;
    std::cin >> tempchar;
    gameSettings.setOVal(tempchar);
    std::cout << "X Value: (Currently - " << gameSettings.getXVal() << ")" << std::endl;
    std::cin >> tempchar;
    gameSettings.setXVal(tempchar);
    std::cout << "Tie Value: (Currently - " << gameSettings.getTieVal() << ")" << std::endl;
    std::cin >> tempchar;
    gameSettings.setTieVal(tempchar);
    std::cout << "------------------------" << std::endl;
    std::cout << "Board Size: (Currently - " << gameSettings.getBoardSize() << ")" << std::endl;
    std::cin >> tempint;
    gameSettings.setBoardSize(tempint);
    std::cout << "Win Length: (Currently - " << gameSettings.getWinLength() << ")" << std::endl;
    std::cin >> tempint;
    gameSettings.setWinLength(tempint);
    std::cout << "------------------------" << std::endl;
    std::cout << "AI Recursion Depth: (Currently - " << gameSettings.getRecursionDepth() << ")" << std::endl;
    std::cin >> tempint;
    gameSettings.setRecursionDepth(tempint);
}