#pragma once

#include <vector>
#include <iostream>
#include <math.h>

#include "tttBoard.h"

struct AIMove {
	AIMove() : x(0), y(0), score(0) {};
	AIMove(int Score) : x(0), y(0), score(Score) {};
	int x;
	int y;
	int score;
};

class tttAI
{
public:
	tttAI() : _boardCount(0) {};
	void init(char AIPlayer);
	AIMove performMove(tttBoard& __board);
	AIMove getBestMove(tttBoard __board, char player, int depth);
	int getBoardCount();
private:
	int _winValue;
	int _lossValue;
	char _aiPlayer;
	char _humanPlayer;
	int _boardCount;
};

