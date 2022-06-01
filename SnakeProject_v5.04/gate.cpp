#include <time.h>
#include <math.h>
#include "gate.h"
#include "Map.h"

void Gate::delGates(const int stage, Map map)	// 게이트 쌍에 위치에 있는 7 -> 1 로 바꾼 후 게이트 소멸
{
	map.mapList[stage][this->getY()][this->getX()] = '1';
	map.mapList[stage][this->getPairPtr()->getY()][this->getPairPtr()->getX()] = '1';
	this->getPairPtr()->~Gate();
	this->~Gate();
}
void Gate::setPairPtr(Gate* pair) {		// Gate의 pairPtr을 통해 Gate 1,2를 한 쌍으로 지정
	this->pairPtr = pair;
	pair->pairPtr =  this;
}

Gate* Gate::getPairPtr() const			// 연결되어 있는 Gate의 포인터를 리턴
{
	return this->pairPtr;
}

void Gate::setY(const int elem)			// Gate의 y 좌표 설정
{
	this->y = elem;
}

void Gate::setX(const int elem)			// Gate의 x 좌표 설정
{
	this->x = elem;
}

void Gate::setPos(const int elemY, const int elemX)	// Gate의 y, x 좌표 설정
{
	this->y = elemY;
	this->x = elemX;
}

void Gate::setExitDirect(const int elem)			// Gate 출구의 방향을 각 Gate 객체에 저장
{
	this->exitDirect = elem;
}

int Gate::getY() const					// Gate의 y 좌표 리턴
{
	return this->y;
}

int Gate::getX() const					// Gate의 x 좌표 리턴
{
	return this->x;
}

int Gate::getExitY() const				// Snake가 들어오는 방향에 따라 알맞는 방향으로 Gate에서 나가도록 y 좌표를 설정
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

int Gate::getExitX() const		// Snake가 들어오는 방향에 따라 알맞는 방향으로 Gate에서 나가도록 x 좌표를 설정
{								// x 좌표를 설정할 때만 headDir을 재설정 해야 오작동이 없다. x 좌표를 더 늦게 설정하므로 이 함수에만 headDir을 설정
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