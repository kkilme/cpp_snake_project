#pragma once
#include "curses.h"

class Score
{
public:
	Score()
	{
		snake_length = 0;
		num_incItem = 0;
		num_decItem = 0;
		num_gate = 0;
	}
	void resetScore();
	void updateScore(WINDOW * win2);
	void setSnakeLength(const int sakeLength);
	void addIncItem();
	void addDecItem();
	void addGate();
private:
	int snake_length;
	int num_incItem;
	int	num_decItem;
	int num_gate;
};
