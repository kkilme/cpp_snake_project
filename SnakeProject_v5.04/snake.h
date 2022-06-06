#pragma once

#include <vector>
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using std::vector;

class SnakePart { //snake�� �̷�� ��ĭ��ĭ�� �κ� - x,y��ǥ�� ����
    
public:
    int x;
    int y;
    
    SnakePart(const int xpos, const int ypos) {
        x = xpos;
        y = ypos;
    }
    SnakePart() {
        x = 0;
        y = 0;
    }
};

bool moveSnake(const int stage); // snake �����̱�, ��ȯ��: ���ӿ��� ���� (true = ���ӿ���)
vector<SnakePart> makeSnake(const int stage); // snake ���� (�������� ����) , stage�� ���ڷ� �־�� ����: ���� ������������ ���� ��ġ�� �ٸ��������� ���� (������ ��ġ ����)
bool setHeadDir(); // Ű �Է¹޾� snake�� �ٶ󺸴� ���� ����