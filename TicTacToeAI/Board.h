#include "Settings.h"

Settings gameSettings;

class Board {
public:
	//default constructor
	Board()
	{
		//board vector reserve
		_board.resize(_board_size);
		for (int i = 0; i < _board_size; i++)
			_board[i].resize(_board_size);
		//board fill blank
		for (int x = 0; x < _board_size; x++)
			for (int y = 0; y < _board_size; y++)
				_board[x][y] = _blank_val;
	}
// Set functions
	//void addState(int _x, int _y) { _board[_x][_y] = _player; 
	void addState(int _x, int _y, char _player) { _board[_x][_y] = _player; }

// Get Functions
	char getState(int _x, int _y) { return _board[_x][_y]; }

	//getBoard() : returns board;
	char getBoard() { return _board[_board_size][_board_size]; }

	//getSize() : returns board size, which is always square.
	int getSize() { return _board.size(); }

	//validMove() : returns if Move is Blank
	bool validMove(int _x, int _y) { return (_board[_x][_y] == _blank_val) && (validBounds(_x,_y)); }
	//validBounds() : returns if Move is on Board
	bool validBounds(int _x, int _y) { 
		if (_x < 0 || _y < 0 || _x >= _board_size || _y >= _board_size) 
			return false; 
		return true; }

	//isFull() : Checks spaces until it finds a blank val, if none exist, returns true
	bool isFull() { for (int x = 0; x < _board_size; x++) { for (int y = 0; y < _board_size; y++) { if (_board[x][y] == _blank_val) { return false; } } } return true; }

	//isVict(char) : Checks if there is a victory on the board, returns char for who won (Can be a Tie)
	char isVict();

private:
	// Const Board Settings, Locally Stored to prevent midgame changes
	const int _board_size = gameSettings.getBoardSize();
	const int _board_win_length = gameSettings.getWinLength();

	// Global Settings, Locally Stored to prevent midgame changes
	char _blank_val = '-';
	char _o_val = 'O';
	char _x_val = 'X';
	char _tie_val = 'T';

	std::vector<std::vector<char>> _board;
};

struct Move {
	Move() : x(0), y(0), score(0) {};
	Move(int _score) : x(0), y(0), score(_score) {};
	Move(int _x, int _y) : x(_x), y(_y), score(0) {};
	Move(int _x, int _y, int _score) : x(_x), y(_y), score(_score) {};
	int x;
	int y;
	int score;
};


char Board::isVict()
{
	static const int xbases[] = { 0, 0, 0, _board_size - 1 };
	static const int ybases[] = { 0, 0, 0, 0 };
	static const int xdirections[] = { 1, 1, 1, -1 };
	static const int xlengths[] = { _board_size - _board_win_length + 1, _board_size, _board_size - _board_win_length + 1, _board_size - _board_win_length + 1 };
	static const int ylengths[] = { _board_size, _board_size - _board_win_length + 1, _board_size - _board_win_length + 1, _board_size - _board_win_length + 1 };
	static const int xmods[] = { 1, 0, 1, -1 };
	static const int ymods[] = { 0, 1, 1, 1 };

	for (int im = 0; im < 4; im++) {
		int xbase = xbases[im];
		int ybase = ybases[im];
		int xdirection = xdirections[im];
		int xlength = xlengths[im];
		int ylength = ylengths[im];
		int xmod = xmods[im];
		int ymod = ymods[im];
		for (int ix = 0; ix < xlength; ix++) {
			for (int iy = 0; iy < ylength; iy++) {
				int bx = (xdirection * ix) + xbase;
				int by = iy + ybase;
				char start_piece = _board[by][bx];
				if (start_piece == _blank_val) {
					continue;
				}
				bool matched = true;
				for (int s = 1; s < _board_win_length; s++) {
					int nx = bx + (xmod * s);
					int ny = by + (ymod * s);
					char next_piece = _board[ny][nx];
					if (start_piece != next_piece) {
						matched = false;
						break;
					}
				}
				if (matched) {
					return start_piece;
				}
			}
		}
	}
	if (isFull())
		return _tie_val;
	return _blank_val;
}

/*
char Board::isVict()
{
	int ostreak = 0, xstreak = 0;
	//Horizontal
	for (int x = 0; x < _board_size; x++) 
	{
		for (int y = 0; y < _board_size; y++)
		{
			if (_board[x][y] == _o_val)
			{
				ostreak++;
				xstreak = 0;
			}
			else if (_board[x][y] == _x_val)
			{
				xstreak++;
				ostreak = 0;
			}
			else
			{
				ostreak = 0;
				xstreak = 0;
			}
			if (ostreak >= _board_win_length)
				return _o_val;
			if (xstreak >= _board_win_length)
				return _x_val;
		}
		ostreak = 0;
		xstreak = 0;
	}
	//Vertical
	for (int y = 0; y < _board_size; y++)
	{
		for (int x = 0; x < _board_size; x++)
		{
			if (_board[x][y] == _o_val)
			{
				ostreak++;
				xstreak = 0;
			}
			else if (_board[x][y] == _x_val)
			{
				xstreak++;
				ostreak = 0;
			}
			else
			{
				ostreak = 0;
				xstreak = 0;
			}
			if (ostreak >= _board_win_length)
				return _o_val;
			if (xstreak >= _board_win_length)
				return _x_val;
		}
		ostreak = 0;
		xstreak = 0;
	}

	
	//Diagonal
	for (int x = 0; x < _board_size; x++)
	{
		for (int i = 0; validBounds(x + i, i); i++)
		{
			if (validBounds(x + i, i))
			{
				if (_board[x + i][i] == _o_val)
				{
					ostreak++;
					xstreak = 0;
				}
				else if (_board[x + i][i] == _x_val)
				{
					xstreak++;
					ostreak = 0;
				}
				else
				{
					ostreak = 0;
					xstreak = 0;
				}
				if (ostreak >= _board_win_length)
					return _o_val;
				if (xstreak >= _board_win_length)
					return _x_val;
			}
		}
		ostreak = 0;
		xstreak = 0;
	}
	
	for (int y = 1; y < _board_size; y++)
	{
		for (int i = 0; validBounds(i, y+i); i++)
		{
			if (validBounds(i, y + i))
			{
				if (_board[i][y + i] == _o_val)
				{
					ostreak++;
					xstreak = 0;
				}
				else if (_board[i][y + i] == _x_val)
				{
					xstreak++;
					ostreak = 0;
				}
				else
				{
					ostreak = 0;
					xstreak = 0;
				}
				if (ostreak >= _board_win_length)
					return _o_val;
				if (xstreak >= _board_win_length)
					return _x_val;
			}
		}
		ostreak = 0;
		xstreak = 0;
	}

	
	//AntiDiagonal
	for (int x = 0; x < _board_size; x++)
	{
		for (int i = 0; validBounds(x + i, _board_size - i - 1); i++)
		{
			if (validBounds(x + i, _board_size - i - 1))
			{
				if (_board[x + i][_board_size - i - 1] == _o_val)
				{
					ostreak++;
					xstreak = 0;
				}
				else if (_board[x - i][_board_size - i - 1] == _x_val)
				{
					xstreak++;
					ostreak = 0;
				}
				else
				{
					ostreak = 0;
					xstreak = 0;
				}
				if (ostreak >= _board_win_length)
					return _o_val;
				if (xstreak >= _board_win_length)
					return _x_val;
			}
		}
		ostreak = 0;
		xstreak = 0;
	}
	for (int y = 1; y < _board_size; y++)
	{
		for (int i = 0; validBounds(i, y - i); i++)
		{
			if (validBounds(i, y - i))
			{
				if (_board[i][y - i] == _o_val)
				{
					ostreak++;
					xstreak = 0;
				}
				else if (_board[i][y - i] == _x_val)
				{
					xstreak++;
					ostreak = 0;
				}
				else
				{
					ostreak = 0;
					xstreak = 0;
				}
				if (ostreak >= _board_win_length)
					return _o_val;
				if (xstreak >= _board_win_length)
					return _x_val;
			}
		}
		ostreak = 0;
		xstreak = 0;
	}
	

	//Check Tie
	if (isFull())
		return _tie_val;

	//Nothing Found
	return _blank_val;
*/
