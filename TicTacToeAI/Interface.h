

#include "GUI.h"

class Interface
{
public:
	void play();
	void AIvsAI(GUI& gui, Board & board);
	void PvsAI(GUI& gui, Board & board);

private:
	int board_count = 0;
	std::vector<Move> replay;
};

void Interface::play()
{
	bool running = true, gamePlayed = false;
	std::vector<Move> emptyReplay;
	do
	{
		Board board;
		GUI gui;
		switch (gui.menu(gamePlayed))
		{
		case 1:
			replay = emptyReplay;
			PvsAI(gui, board);
			gamePlayed = true;
			break;
		case 2:
			std::cout << std::endl << ". . . Generating Moves . . ." << std::endl;
			replay = emptyReplay;
			AIvsAI(gui, board);
			gamePlayed = true;
			break;
			if (gamePlayed)
			{
		case 3:
			gui.saveBoard(replay);
			break;
		case 4:
			gui.replayBoard(replay);
			break;
		case 5:
			gui.processedCount(board_count);
			break;
			}
		case 6:
			gui.settings();
			break;
		case 7:
			running = false;
			break;
		default:
			std::cout << "Please choose an available response." << std::endl;
			break;
		}
	} while (running);
}

void Interface::AIvsAI(GUI& gui, Board& board) {
	AI AIX, AIO;
	Move replaymv;
	char winner;
	AIX.init(gameSettings.getXVal());
	AIO.init(gameSettings.getOVal());
	std::cout << std::endl << std::endl;
	do
	{
		replaymv = AIX.performMoveMM(board);
		winner = board.isVict();
		std::cout << gui.print(board) << std::endl;

		replay.push_back(replaymv);

		if (winner == gameSettings.getBlankVal())
		{
			replaymv = AIO.performMoveMM(board);
			replay.push_back(replaymv);
			winner = board.isVict();
			std::cout << gui.print(board) << std::endl;
		}
	} while (winner == gameSettings.getBlankVal());
	std::cout << gui.print(board) << std::endl;
	if (winner == gameSettings.getXVal() || winner == gameSettings.getOVal())
	{
		std::cout << "The winner is: " << winner << std::endl;
	}
	else
	{
		std::cout << "The game is a tie!" << std::endl;
	}
	board_count = AIX.getBoardProcessed() + AIO.getBoardProcessed();
}

void Interface::PvsAI(GUI& gui, Board& board) {
	int x_value, y_value;
	char player = gameSettings.getXVal(), winner;
	Move replaymv;
	AI ai;
	ai.init(gameSettings.getOVal());
	std::cout << gui.print(board) << std::endl;
	do
	{
		std::cout << "X-Coord: ";
		std::cin >> x_value;
		std::cout << "Y-Coord: ";
		std::cin >> y_value;
		std::cout << "\n\n";

		board.addState(x_value - 1, y_value - 1, player);
		replaymv.x = x_value - 1;
		replaymv.y = y_value - 1;
		replay.push_back(replaymv);
		replaymv = ai.performMoveMM(board);
		replay.push_back(replaymv);
		std::cout << gui.print(board) << std::endl;
		winner = board.isVict();
	} while (winner == gameSettings.getBlankVal());
	std::cout << gui.print(board) << std::endl;
	if (winner == gameSettings.getXVal() || winner == gameSettings.getOVal())
	{
		std::cout << "The winner is: " << winner << std::endl;
	}
	else
	{
		std::cout << "The game is a tie!" << std::endl;
	}
	board_count = ai.getBoardProcessed();
}