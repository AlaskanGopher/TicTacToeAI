#pragma once

#include <string>

// -- SETTINGS --
#define BOARD_SIZE 5 //tttBoard print function works for < 9
#define WIN_LENGTH 4

#define BLANK_VAL '-' // Changes Blank Value
#define O_VAL 'O' // Changes O Value
#define X_VAL 'X' // Changes X Value
#define TIE_VAL 'T' // Changes T Value

#define RECURSION_DEPTH 5 // recursive char[5][5] can fit in 8gb approx. 6.33467 DEPTH

// X color
//#define COLOR_BLUE "\x1b[1;36m"
#define COLOR_BLUE ""
// O color
//#define COLOR_RED "\x1b[1;31m"
#define COLOR_RED ""
// reset color
//#define COLOR_RESET "\x1b[0m"
#define COLOR_RESET ""

// -- SETTINGS --

//const char BLANK_VAL = '-';
//const char O_VAL = 'O';
//const char X_VAL = 'X';
//const char TIE_VAL = 'T';

class tttBoard
{
public:
	tttBoard()
	{
		for (int x = 0; x < BOARD_SIZE; x++)
			for (int y = 0; y < BOARD_SIZE; y++)
				__board[x][y] = BLANK_VAL;
	}
	void reset();
	void addState(int _x, int _y, char _player);
	char getState(int _x, int _y);
	char checkVict();

	std::string print();
private:
	char __board[BOARD_SIZE][BOARD_SIZE];
};

