#include "Score.h"

#define COND_SNAKELENGTH 6//6
#define COND_INCITEM 4//4
#define COND_DECITEM 2
#define COND_GATE 2//2

void Score::resetScore() 	// ���� ����
{
	snake_length = 3;			// �ʱ� ���� ����
	num_incItem = 0;
	num_decItem = 0;
	num_gate = 0;
}

void Score::updateScore(WINDOW* win2)		// ���� ȭ�� ������Ʈ
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

void Score::addIncItem()		// inc Item�� ���� ������ 1�� ����
{
	num_incItem++;
}

void Score::addDecItem()		// dec Item�� ���� ������ 1�� ����
{
	num_decItem++;
}

void Score::addGate()			// gate�� ����� ������ 1�� ����
{
	num_gate++;
}

int Score::getDecItem()	const		// ���� dec item ����
{
	return num_decItem;
}

bool Score::isClear(WINDOW* win3)
{
	// snake ���� Ȯ�� �� �̼� ȭ�� ������Ʈ
	mvwprintw(win3, 1, 1, "         Mission");
	if (snake_length > COND_SNAKELENGTH || snake_length == COND_SNAKELENGTH) 
	{
		check = 'V';		// Snake �̼��� �Ϸ��ߴٸ� üũ
		stageClear = true;	// ù ���ǹ��̱� ������ ����
	}
	else
	{
		check = ' ';
		stageClear = false;
	}
	mvwprintw(win3, 2, 1, "* Snake Length >= %d : (%c)", COND_SNAKELENGTH, check);
	// inc item ���� Ȯ�� �� �̼� ȭ�� ������Ʈ
	if (num_incItem > COND_INCITEM || num_incItem == COND_INCITEM)
	{
		check = 'V';
		stageClear &= true;		// ù ���ǹ��� �ƴϱ� ������ & ������ Ȱ��
	}
	else
	{
		check = ' ';
		stageClear =  false;
	}
	mvwprintw(win3, 3, 1, "* Inc Item >= %d : (%c)", COND_INCITEM, check);
	// dec item ���� Ȯ�� �� �̼� ȭ�� ������Ʈ
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
	// Gate ��� Ƚ�� Ȯ�� �� �̼� ȭ�� ������Ʈ
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
