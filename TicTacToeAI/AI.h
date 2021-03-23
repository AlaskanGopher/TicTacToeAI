
#include "Board.h"
#include <memory>
#include <iostream>

class AI {
public:
	void init(char AIPlayer);

	//Function for Min-Max Algorithm
	Move performMoveMM(Board& board);
	//Function for MSTs Algorithm
	Move performMoveMST() {};

	//Analyze Board
	int getBoardProcessed() { return _boardCount; }
private:
	Move getBestMoveMM(Board __board, char player, int depth);
	int _boardCount = 0;
	char _aiSymbol; //AI's Symbol, Symbol defined in Settings
	char _oppSymbol; //Opponent Symbol, Symbol defined in Settings
};

class Node {
public:
	
private:
	Node* parent = nullptr;
	std::vector<Move> potentialMoves;
	std::vector<std::unique_ptr<Node>> children;
};

void AI::init(char AIPlayer)
{
	_aiSymbol = AIPlayer;
	if (_aiSymbol == gameSettings.getOVal()) {
		_oppSymbol = gameSettings.getXVal();
	}
	else
	{
		_oppSymbol = gameSettings.getOVal();
	}
}

Move AI::performMoveMM(Board& board)
{
	Move bestMove = getBestMoveMM(board, _aiSymbol, 0);
	board.addState(bestMove.x, bestMove.y, _aiSymbol);
	return bestMove;
}

Move AI::getBestMoveMM(Board board, char player, int depth)
{
	_boardCount++;
	// Base Case
	char victory = board.isVict();
	if (victory == _aiSymbol) {
		//std::cout << _aiSymbol << ": Win!" << std::endl;
		return Move(1);
	}
	else if (victory == _oppSymbol) {
		//std::cout << _oppSymbol << ": Win!" << std::endl;
		return Move(-100);
	}
	else if (victory == gameSettings.getTieVal())
	{
		return Move(0);
	}

	std::vector<Move> moves;
	// Recursive Case
	if (depth < gameSettings.getRecursionDepth())
	{
		depth++;
		// Recursive Case
		for (int y = 0; y < board.getSize(); y++) {
			for (int x = 0; x < board.getSize(); x++) {
				if (board.validMove(x,y))
				{
					Move move;
					move.x = x;
					move.y = y;
					board.addState(x, y, player);
					if (player == _aiSymbol) {
						move.score = getBestMoveMM(board, _oppSymbol, depth).score;
					}
					else {
						move.score = getBestMoveMM(board, _aiSymbol, depth).score;
					}
					moves.push_back(move);
					board.addState(x, y, gameSettings.getBlankVal());
				}
			}
		}

		//Computes all previous recursed functions
		int bestMove = 0;
		int overallScore = 0;
		if (player == _aiSymbol) {
			int bestScore = -100000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score > bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
				}
				overallScore += moves[i].score;
			}
		}
		else {
			int bestScore = 100000;
			for (int i = 0; i < moves.size(); i++)
			{
				if (moves[i].score < bestScore) {
					bestMove = i;
					bestScore = moves[i].score;
				}
				overallScore += moves[i].score;
			}
		}
		moves[bestMove].score = overallScore;
		return moves[bestMove];
	}
	
	return Move(0);
}