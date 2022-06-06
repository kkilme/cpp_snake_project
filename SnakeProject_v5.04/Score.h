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
	int snake_length;		// 뱀의 길이
	int num_incItem;		// incItem을 먹은 갯수
	int	num_decItem;		// decItem을 먹은 갯수
	int num_gate;			// Gate를 통과한 수
	char check;				// mission 성공 여부를 표현할 문자 -> 'V' or ' '
	bool stageClear;		// clear 여부
};
