#include <time.h>
#include <math.h>
#include "gate.h"
#include "Map.h"

void Gate::delGates(const int stage, Map map)	// ����Ʈ �ֿ� ��ġ�� �ִ� 7 -> 1 �� �ٲ� �� ����Ʈ �Ҹ�
{
	map.mapList[stage][this->getY()][this->getX()] = '1';
	map.mapList[stage][this->getPairPtr()->getY()][this->getPairPtr()->getX()] = '1';
	this->getPairPtr()->~Gate();
	this->~Gate();
}
void Gate::setPairPtr(Gate* pair) {		// Gate�� pairPtr�� ���� Gate 1,2�� �� ������ ����
	this->pairPtr = pair;
	pair->pairPtr =  this;
}

Gate* Gate::getPairPtr() const			// ����Ǿ� �ִ� Gate�� �����͸� ����
{
	return this->pairPtr;
}

void Gate::setY(const int elem)			// Gate�� y ��ǥ ����
{
	this->y = elem;
}

void Gate::setX(const int elem)			// Gate�� x ��ǥ ����
{
	this->x = elem;
}

void Gate::setPos(const int elemY, const int elemX)	// Gate�� y, x ��ǥ ����
{
	this->y = elemY;
	this->x = elemX;
}

void Gate::setExitDirect(const int elem)			// Gate �ⱸ�� ������ �� Gate ��ü�� ����
{
	this->exitDirect = elem;
}

int Gate::getY() const					// Gate�� y ��ǥ ����
{
	return this->y;
}

int Gate::getX() const					// Gate�� x ��ǥ ����
{
	return this->x;
}

int Gate::getExitY() const				// Snake�� ������ ���⿡ ���� �˸´� �������� Gate���� �������� y ��ǥ�� ����
{
	int res = 0;
	switch (this->exitDirect)
	{
	case LEFT:
		res = this->y;
		break;
	case RIGHT:
		res =  this->y;
		break;
	case UP:
		res =  this->y - 1;
		break;
	case DOWN:
		res =  this->y + 1;
		break;
	case UP_LEFT:
		if (headDir == UP || headDir == RIGHT)
		{
			res =  this->y - 1;
			break;
		}
		else
		{
			res =  this->y;
			break;
		}
	case UP_RIGHT:
		if (headDir == RIGHT || headDir == DOWN)
		{
			res =  this->y;
			break;
		}
		else
		{
			res =  this->y - 1;
			break;
		}
	case DOWN_RIGHT:
		if (headDir == DOWN || headDir == LEFT)
		{
			res =  this->y + 1;
			break;
		}
		else
		{
			res =  this->y;
			break;
		}
	case DOWN_LEFT:
		if (headDir == LEFT || headDir == UP)
		{
			res =  this->y;
			break;
		}
		else
		{
			res =  this->y + 1;
			break;
		}
	}
	return res;
}

int Gate::getExitX() const		// Snake�� ������ ���⿡ ���� �˸´� �������� Gate���� �������� x ��ǥ�� ����
{								// x ��ǥ�� ������ ���� headDir�� �缳�� �ؾ� ���۵��� ����. x ��ǥ�� �� �ʰ� �����ϹǷ� �� �Լ����� headDir�� ����
	int res = 0;
	switch (this->exitDirect)
	{
	case LEFT:
		headDir = LEFT;
		res = this->x - 1;
		break;
	case RIGHT:
		headDir = RIGHT;
		res =  this->x + 1;
		break;
	case UP:
		headDir = UP;
		res =  this->x;
		break;
	case DOWN:
		headDir = DOWN;
		res =  this->x;
		break;
	case UP_LEFT:
		if (headDir == UP || headDir == RIGHT)
		{
			headDir = UP;
			res = this->x;
			break;
		}
		else
		{
			headDir = LEFT;
			res =  this->x - 1;
			break;
		}
	case UP_RIGHT:
		if (headDir == RIGHT || headDir == DOWN)
		{
			headDir = RIGHT;
			res =  this->x + 1;
			break;
		}
		else
		{
			headDir = UP;
			res =  this->x;
			break;
		}
	case DOWN_RIGHT:
		if (headDir == DOWN || headDir == LEFT)
		{
			headDir = DOWN;
			res =  this->x;
			break;
		}
		else
		{
			headDir = RIGHT;
			res =  this->x + 1;
			break;
		}
	case DOWN_LEFT:
		if (headDir == LEFT || headDir == UP)
		{
			headDir = LEFT;
			res =  this->x - 1;
			break;
		}
		else
		{
			headDir = DOWN;
			res =  this->x;
			break;
		}
	}
	return res;
}