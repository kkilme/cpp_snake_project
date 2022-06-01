#pragma once
#include "Map.h"
extern int headDir;

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_RIGHT 6
#define DOWN_LEFT 7

class Gate
{
public:
	Gate(int elemY = 0, int elemX = 0)
	{
		y = elemY;
		x = elemX;
		pairPtr = NULL;
		exitDirect = NULL;
	}
	~Gate()
	{
		y = 0;
		x = 0;
		pairPtr = NULL;
		exitDirect = NULL;
	}
	void delGates(const int stage, Map map);
	void setPairPtr(Gate * pair);
	Gate * getPairPtr() const;
	void setY(const int elem);
	void setX(const int elem);
	void setPos(const int elemY, const int elemX);
	void setExitDirect(const int elem);
	int getY() const;
	int getX() const;
	int getExitY() const;
	int getExitX() const;
private:
	int y;		// Gate의 y좌표
	int x;		// Gate의 x좌표
	Gate * pairPtr;	// Gate 쌍의 포인터
	int exitDirect;	// Gate 에서 나갈 수 있는 방향 설정
};
