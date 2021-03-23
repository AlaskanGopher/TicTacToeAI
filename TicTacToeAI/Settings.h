
// X color
#define COLOR_BLUE "\x1b[1;36m"
//#define COLOR_BLUE ""
// O color
#define COLOR_RED "\x1b[1;31m"
//#define COLOR_RED ""
// reset color
#define COLOR_RESET "\x1b[0m"
//#define COLOR_RESET ""

#include <vector>

enum AIType { MinMax, MCTs };

class Settings {
public:
	//Set Functions
	void setBlankVal(char& blankval) { _blank_val = blankval;  }
	void setOVal(char& oval) { _o_val = oval; }
	void setXVal(char& xval) { _x_val = xval; }
	void setTieVal(char& tieval) { _tie_val = tieval; }

	void setBoardSize(int& boardsize) { _board_size = boardsize; }
	void setWinLength(int& winlength) { _board_win_length = winlength; }

	void setRecursionDepth(int& recursion) { _AI_recursion_depth = recursion; }
	//Get Functions
	char getBlankVal() const {
		return _blank_val;
	}
	char getOVal() const {
		return _o_val;
	}
	char getXVal() const {
		return _x_val;
	}
	char getTieVal() const {
		return _tie_val;
	}

	int getBoardSize() const {
		return _board_size;
	}
	int getWinLength() const {
		return _board_win_length;
	}

	int getRecursionDepth() const {
		return _AI_recursion_depth;
	};

private:
	// Global Settings
	char _blank_val = '-';
	char _o_val = 'O';
	char _x_val = 'X';
	char _tie_val = 'T';
	// Board Settings
	int _board_size = 5;
	int _board_win_length = 4;
	// AI Settings
	int _AI_recursion_depth = 5;
	AIType _ai_one = MinMax;
	AIType _ai_two = MCTs;
};

/*
class AISettings {
public:
	//Set Functions
	AISettings(AIType & ait) : _ai_type(ait) {}
	void setAIType(AIType & ait) { _ai_type = ait; }
	void setAIrecursion(int& recur) { _recursion_depth = recur; }
	//Get Functions
	AIType getAIType() { return _ai_type; }
	int getRecursionDepth() { return _recursion_depth;  }

private:
	int _recursion_depth = 5;
	AIType _ai_type = MinMax;
};
*/