#include "Score.h"

#define COND_SNAKELENGTH 6//6
#define COND_INCITEM 4//4
#define COND_DECITEM 2
#define COND_GATE 2//2

void Score::resetScore() 	// 점수 리셋
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

void Score::addSnakeLength()
{
	snake_length++;
}

void Score::subSnakeLength()
{
	snake_length--;
}

void Score::addIncItem()		// inc Item을 먹을 때마다 1씩 증가
{
	num_incItem++;
}

void Score::addDecItem()		// dec Item을 먹을 때마다 1씩 증가
{
	num_decItem++;
}

void Score::addGate()			// gate를 통과할 때마다 1씩 증가
{
	num_gate++;
}

int Score::getDecItem()	const		// 먹은 dec item 리턴
{
	return num_decItem;
}

bool Score::isClear(WINDOW* win3)
{
	// snake 길이 확인 후 미션 화면 업데이트
	mvwprintw(win3, 1, 1, "         Mission");
	if (snake_length > COND_SNAKELENGTH || snake_length == COND_SNAKELENGTH) 
	{
		check = 'V';		// Snake 미션을 완료했다면 체크
		stageClear = true;	// 첫 조건문이기 때문에 선언
	}
	else
	{
		check = ' ';
		stageClear = false;
	}
	mvwprintw(win3, 2, 1, "* Snake Length >= %d : (%c)", COND_SNAKELENGTH, check);
	// inc item 갯수 확인 후 미션 화면 업데이트
	if (num_incItem > COND_INCITEM || num_incItem == COND_INCITEM)
	{
		check = 'V';
		stageClear &= true;		// 첫 조건문이 아니기 때문에 & 연산을 활용
	}
	else
	{
		check = ' ';
		stageClear =  false;
	}
	mvwprintw(win3, 3, 1, "* Inc Item >= %d : (%c)", COND_INCITEM, check);
	// dec item 갯수 확인 후 미션 화면 업데이트
	if (num_decItem < COND_DECITEM)
	{
		check = 'V';
		stageClear &= true;
	}
	else
	{
		check = ' ';
		stageClear = false;
	}
	mvwprintw(win3, 4, 1, "* Dec Item < %d : (%c)", COND_DECITEM, check);
	// Gate 통과 횟수 확인 후 미션 화면 업데이트
	if (num_gate > COND_GATE || num_gate == COND_GATE)
	{
		check = 'V';
		stageClear &= true;
	}
	else
	{
		check = ' ';
		stageClear = false;
	}
	mvwprintw(win3, 5, 1, "* Gate >= %d : (%c)", COND_GATE, check);
	return stageClear;
}
