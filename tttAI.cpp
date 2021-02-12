#include "tttAI.h"

void tttAI::init(char AIPlayer)
{
	_aiPlayer = AIPlayer;
	if (_aiPlayer == X_VAL) {
		_humanPlayer = O_VAL;
	}
	else
	{
		_humanPlayer = X_VAL;
	}
}
AIMove tttAI::performMove(tttBoard& __board)
{
	AIMove bestMove = getBestMove(__board, _aiPlayer, 0);
	__board.addState(bestMove.x, bestMove.y, _aiPlayer);
	return bestMove;
}

AIMove tttAI::getBestMove(tttBoard __board, char player, int depth)
{
	_boardCount++;
	// Base Case
	char victory = __board.checkVict();
	if (victory == _aiPlayer) {
		//std::cout << _aiPlayer << ": Win!" << std::endl;
		return AIMove(pow(2, RECURSION_DEPTH - depth));
	}
	else if (victory == _humanPlayer) {
		//std::cout << _humanPlayer << ": Win!" << std::endl;
		return AIMove(0 - pow(2, RECURSION_DEPTH - depth));
	}
	else if (victory == TIE_VAL)
	{
		return AIMove(0);
	}

	std::vector<AIMove> moves;


	// Recursive Case
	if (depth < RECURSION_DEPTH)
	{
		depth++;
		// Recursive Case
		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				if (__board.getState(x, y) == BLANK_VAL)
				{
					AIMove move;
					move.x = x;
					move.y = y;
					__board.addState(x, y, player);
					if (player == _aiPlayer) {
						move.score = getBestMove(__board, _humanPlayer, depth).score;
					}
					else {
						move.score = getBestMove(__board, _aiPlayer, depth).score;
					}
					moves.push_back(move);
					__board.addState(x, y, BLANK_VAL);
				}
			}
		}

		//Computes all previous recursed functions
		int bestMove = 0;
		int overallBestScore = 0;
		if (player == _aiPlayer) {
			int bestScore = -10000000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score > bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
					
				}
				overallBestScore += bestScore;
			}
		}
		else {
			int bestScore = 10000000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score < bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
				}
				overallBestScore += bestScore;
			}
		}
		moves[bestMove].score = overallBestScore;
		return moves[bestMove];
	}
	return 0;
}

int tttAI::getBoardCount()
{
	return _boardCount;
}