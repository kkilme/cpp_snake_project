#pragma once
#include "curses.h"

class Score
{
public:
	Score()
	{
		snake_length = 3;
		num_incItem = 0;
		num_decItem = 0;
		num_gate = 0;
		check = ' ';
		stageClear = false;
	}
	void resetScore()  ;
	void updateScore(WINDOW * win2);
	void addSnakeLength();
	void subSnakeLength();
	void addIncItem();
	void addDecItem();
	void addGate();
	int  getDecItem() const ;
	bool isClear(WINDOW* win3);
private:
	int snake_length;		// ���� ����
	int num_incItem;		// incItem�� ���� ����
	int	num_decItem;		// decItem�� ���� ����
	int num_gate;			// Gate�� ����� ��
	char check;				// mission ���� ���θ� ǥ���� ���� -> 'V' or ' '
	bool stageClear;		// clear ����
};
