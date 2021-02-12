#include "tttBoard.h"

void tttBoard::reset()
{
	for (int x = 0; x < BOARD_SIZE; x++)
		for (int y = 0; y < BOARD_SIZE; y++)
			__board[x][y] = BLANK_VAL;
}

void tttBoard::addState(int _x, int _y, char _player)
{
	__board[_x][_y] = _player;
}

char tttBoard::getState(int _x, int _y)
{
	return __board[_x][_y];
}

char tttBoard::checkVict()
{
    static const int xbases[] = { 0, 0, 0, BOARD_SIZE - 1 };
    static const int ybases[] = { 0, 0, 0, 0 };
    static const int xdirections[] = { 1, 1, 1, -1 };
    static const int xlengths[] = { BOARD_SIZE - WIN_LENGTH + 1, BOARD_SIZE, BOARD_SIZE - WIN_LENGTH + 1, BOARD_SIZE - WIN_LENGTH + 1 };
    static const int ylengths[] = { BOARD_SIZE, BOARD_SIZE - WIN_LENGTH + 1, BOARD_SIZE - WIN_LENGTH + 1, BOARD_SIZE - WIN_LENGTH + 1 };
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
                char start_piece = __board[by][bx];
                if (start_piece == BLANK_VAL) {
                    continue;
                }
                bool matched = true;
                for (int s = 1; s < WIN_LENGTH; s++) {
                    int nx = bx + (xmod * s);
                    int ny = by + (ymod * s);
                    char next_piece = __board[ny][nx];
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
	for (int x = 0; x < BOARD_SIZE; x++)
	{
		for (int y = 0; y < BOARD_SIZE; y++)
		{
            if (__board[x][y] == BLANK_VAL)
                return BLANK_VAL;
		}
	}

	return TIE_VAL;
}

std::string tttBoard::print()
{
    std::string _tempstr;
    char __state;
    _tempstr = "\n  ";
    for (int x_line = 0; x_line < BOARD_SIZE; x_line++)
    {
        _tempstr += std::to_string(x_line + 1);
        _tempstr += " ";
    }
    _tempstr += "\n";
    for (int y = 0; y < BOARD_SIZE; y++)
    {
        _tempstr += std::to_string(y + 1);
        _tempstr += " ";
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            __state = __board[x][y];
            if (__state == X_VAL) {
                _tempstr += COLOR_BLUE;
                _tempstr += __state;
                _tempstr += " ";
            }
            else if (__state == O_VAL) {
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