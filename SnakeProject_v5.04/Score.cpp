#include "Score.h"

void Score::resetScore()
{
	snake_length = 3;
	num_incItem = 0;
	num_decItem = 0;
	num_gate = 0;
}

void Score::updateScore(WINDOW* win2)
{
	mvwprintw(win2, 1, 1, "Snake Length : %d", snake_length);
	mvwprintw(win2, 2, 1, "Increase item : %d", num_incItem);
	mvwprintw(win2, 3, 1, "Decrease item : %d", num_decItem);
	mvwprintw(win2, 4, 1, "Used gate : %d", num_gate);
}

void Score::setSnakeLength(const int snakeLength)
{
	snake_length = snakeLength;
}

void Score::addIncItem()
{
	num_incItem++;
}

void Score::addDecItem()
{
	num_decItem++;
}

void Score::addGate()
{
	num_gate++;
}