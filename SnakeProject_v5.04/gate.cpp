#include <time.h>
#include <math.h>
#include "gate.h"
#include "Map.h"

void Gate::delGates(const int stage, Map map)
{
	map.mapList[stage][this->getY()][this->getX()] = '1';
	map.mapList[stage][this->getPairPtr()->getY()][this->getPairPtr()->getX()] = '1';
	this->getPairPtr()->~Gate();
	this->~Gate();
}
void Gate::setPairPtr(Gate* pair) {
	this->pairPtr = pair;
	pair->pairPtr =  this;
}

Gate* Gate::getPairPtr() const
{
	return this->pairPtr;
}

void Gate::setY(const int elem)
{
	this->y = elem;
}

void Gate::setX(const int elem)
{
	this->x = elem;
}

void Gate::setPos(const int elemY, const int elemX)
{
	this->y = elemY;
	this->x = elemX;
}

void Gate::setExitDirect(const int elem)
{
	this->exitDirect = elem;
}

int Gate::getY() const
{
	return this->y;
}
int Gate::getX() const
{
	return this->x;
}

int Gate::getExitY() const
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
		if (headDir == UP)
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
		if (headDir == RIGHT)
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
		if (headDir == DOWN)
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
		if (headDir == LEFT)
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

int Gate::getExitX() const
{
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
		if (headDir == UP)
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
		if (headDir == RIGHT)
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
		if (headDir == DOWN)
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
		if (headDir == LEFT)
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