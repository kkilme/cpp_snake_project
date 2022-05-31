#include "Score.h"

void Score::resetScore()		// 점수 리셋
{
	snake_length = 3;			// 초기 뱀의 길이
	num_incItem = 0;
	num_decItem = 0;
	num_gate = 0;
}

void Score::updateScore(WINDOW* win2)		// 점수 화면 업데이트
{
	mvwprintw(win2, 1, 1, "Snake Length : %d", snake_length);
	mvwprintw(win2, 2, 1, "Increase item : %d", num_incItem);
	mvwprintw(win2, 3, 1, "Decrease item : %d", num_decItem);
	mvwprintw(win2, 4, 1, "Used gate : %d", num_gate);
}

void Score::setSnakeLength(const int snakeLength)	// 뱀의 길이를 입력 받아 설정
{
	snake_length = snakeLength;
}

void Score::addIncItem()		// incItem을 먹을 때마다 1씩 증가
{
	num_incItem++;
}

void Score::addDecItem()		// decItem을 먹을 때마다 1씩 증가
{
	num_decItem++;
}

void Score::addGate()			// gate를 통과할 때마다 1씩 증가
{
	num_gate++;
}