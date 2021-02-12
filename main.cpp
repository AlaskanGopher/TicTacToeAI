//CS_F405_HW1_AI Interface
//This will encompass the interface from user to AI, and AI to AI.

#include <iostream>
#include <fstream>
#include "tttAI.h"

void AIVSAI(tttBoard _board);
void PlayerVSAI(tttBoard _board);
void SaveBoard();
void ReplayBoard();

int board_count = 0;
std::vector<AIMove> replay;

int main()
{
	bool running = true, gamePlayed = false;
	int response1;
	std::vector<AIMove> emptyReplay;
	do
	{
		std::cout << "Would you like to play against an AI or do you wish to watch a game?" << std::endl;
		std::cout << "1. Play Against an AI" << std::endl;
		std::cout << "2. Watch AI vs AI" << std::endl;
		if (gamePlayed)
		{
			std::cout << "3. Save Last Game" << std::endl;
			std::cout << "4. Replay Last Game" << std::endl;
			std::cout << "5. Boards Processed in Last Game" << std::endl;
		}
		std::cout << "6. Exit" << std::endl;
		std::cin >> response1;
		tttBoard board;
		switch (response1)
		{
		case 1:
			replay = emptyReplay;
			PlayerVSAI(board);
			gamePlayed = true;
			break;
		case 2:
			std::cout << std::endl << ". . . Generating Moves . . ." << std::endl;
			replay = emptyReplay;
			AIVSAI(board);
			gamePlayed = true;
			break;
			if (gamePlayed)
			{
		case 3:
			SaveBoard();
			break;
		case 4:
			ReplayBoard();
			break;
		case 5:
			std::cout << board_count << " Boards were processed in that last game." << std::endl;
			break;
			}
		case 6:
			running = false;
			break;
		default:
			std::cout << "Please choose an available response." << std::endl;
			break;
		}
	} while (running);

	return 0;
}

void AIVSAI(tttBoard _board)
{
	tttAI AIX, AIO;
	AIMove replaymv;
	char winner;
	AIX.init(X_VAL);
	AIO.init(O_VAL);
	std::cout << std::endl << std::endl;
	do
	{
		replaymv = AIX.performMove(_board);
		winner = _board.checkVict();
		std::cout << _board.print() << std::endl;

		replay.push_back(replaymv);

		if (winner == BLANK_VAL)
		{
			replaymv = AIO.performMove(_board);
			replay.push_back(replaymv);
			winner = _board.checkVict();
			std::cout << _board.print() << std::endl;
		}
	} while (winner == BLANK_VAL);
	std::cout << _board.print() << std::endl;
	if (winner == X_VAL || winner == O_VAL)
	{
		std::cout << "The winner is: " << winner << std::endl;
	}
	else
	{
		std::cout << "The game is a tie!" << std::endl;
	}
	board_count = AIX.getBoardCount() + AIO.getBoardCount();
}

void  PlayerVSAI(tttBoard _board)
{
	int x_value, y_value;
	char player = X_VAL, winner;
	AIMove replaymv;
	tttAI AI;
	AI.init(O_VAL);
	std::cout << _board.print() << std::endl;
	do
	{
		std::cout << "X-Coord: ";
		std::cin >> x_value;
		std::cout << "Y-Coord: ";
		std::cin >> y_value;
		std::cout << "\n\n";

		_board.addState(x_value-1, y_value-1, player);
		replaymv.x = x_value - 1;
		replaymv.y = y_value - 1;
		replay.push_back(replaymv);
		replaymv = AI.performMove(_board);
		replay.push_back(replaymv);
		std::cout << _board.print() << std::endl;
		winner = _board.checkVict();
	} 
	while(winner == BLANK_VAL);
	std::cout << _board.print() << std::endl;
	if (winner == X_VAL || winner == O_VAL)
	{
		std::cout << "The winner is: " << winner << std::endl;
	}
	else
	{
		std::cout << "The game is a tie!" << std::endl;
	}
	board_count = AI.getBoardCount();
}

void SaveBoard()
{
	tttBoard board;
	std::ofstream print("last_game.txt");
	for (int i = 0; i < replay.size(); i++)
	{
		board.addState(replay[i].x, replay[i].y, X_VAL);
		print << board.print();
		i++;
		if (i < replay.size()) {
			board.addState(replay[i].x, replay[i].y, O_VAL);
			print << board.print();
		}
	}
	char winner = board.checkVict();
	if (winner == X_VAL || winner == O_VAL)
	{
		print << "The winner is: " << winner << std::endl;
	}
	else
	{
		print << "The game is a tie!" << std::endl;
	}
	print.close();
}
void ReplayBoard()
{
	tttBoard board;
	for (int i = 0; i < replay.size(); i++)
	{
		board.addState(replay[i].x, replay[i].y, X_VAL);
		std::cout << board.print();
		i++;
		if (i < replay.size()) {
			board.addState(replay[i].x, replay[i].y, O_VAL);
			std::cout << board.print();
		}
	}
	char winner = board.checkVict();
	if (winner == X_VAL || winner == O_VAL)
	{
		std::cout << "The winner is: " << winner << std::endl;
	}
	else
	{
		std::cout << "The game is a tie!" << std::endl;
	}
}