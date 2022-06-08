#include "snake.h"
#include "Map.h"
#include "ItemClass.h"
#include "gate.h"
#include "Score.h"

#define WALL '1'
#define INC_ITEM '5'
#define DEC_ITEM '6'
#define SNAKE_TAIL '4'
#define GATE '7'

int headDir; // �Ӹ� ����
int dir[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; // ��,������,�Ʒ�,���� ���� - headDir�� ���� snake �̵� �� ���
extern vector<SnakePart> snake;
extern Map map;
extern ItemClass item;
extern Gate Gate1, Gate2;
extern Score score;


vector<SnakePart> makeSnake(const int stage) {
    vector<SnakePart> tempsnake; // snake ����
    tempsnake.push_back(SnakePart(15, 16)); // snake �Ӹ��� ��(���������� �߾� ��ġ)
    tempsnake.push_back(SnakePart(15, 17)); 
    tempsnake.push_back(SnakePart(15, 18)); // snake ���� 2�� (ó�� ���̴� 3)

    /*�׽�Ʈ�� �ڵ� - ó�� ���� 6��*//*
    tempsnake.push_back(SnakePart(16, 18)); 
    tempsnake.push_back(SnakePart(17, 18));
    tempsnake.push_back(SnakePart(17, 19));*/
    /**********************************/

    headDir = UP; // ó�� �Ӹ� ������ ����
    return tempsnake;
}

bool setHeadDir() {
    int key = getch();
    switch (key) {
        case KEY_UP: // ���ʹ���Ű ��������
            if (headDir != DOWN) {
                headDir = UP;
                return false;
            }
            else {
                return true; // ���ϰ�: ���ӿ��� ����
            }
        case KEY_RIGHT:
            if (headDir != LEFT) {
                headDir = RIGHT;
                return false;
            }
            else {
                return true;
            }
        case KEY_DOWN:
            if (headDir != UP) {
                headDir = DOWN;
                return false;
            }
            else {
                return true;
            }
        case KEY_LEFT:
            if (headDir != RIGHT) {
                headDir = LEFT;
                return false;
            }
            else {
                return true;
            }
           
    }
    return false;
}

bool moveSnake(const int stage) {
    int headNextX = snake[0].x + dir[headDir][0]; // �Ӹ� ������ġ x
    int headNextY = snake[0].y + dir[headDir][1]; // �Ӹ� ������ġ y
    bool checkIncItem = false; // ������ ������'5'�� true
    bool checkDecItem = false; // ������ ������'6'�� true

    if (map.mapList[stage][headNextY][headNextX] == INC_ITEM) { //������(INC_ITEM) '5'�� �浹�Ҷ��� ����Ǽ� üũ
        checkIncItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; //������ ����Ȯ���ϴ� ���� ����
        score.addIncItem();
    }

    else if (map.mapList[stage][headNextY][headNextX] == DEC_ITEM) { //������(DEC_ITEM) '6'�� �浹�Ҷ��� ����Ǽ� üũ
        checkDecItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; 
        score.addDecItem();
    }

    if (map.mapList[stage][headNextY][headNextX] == WALL) { //��(BLOCK) '1'�� �浹
        return true;
    }
    else if(map.mapList[stage][headNextY][headNextX] == SNAKE_TAIL && !(headNextX == snake[snake.size()-1].x && headNextY == snake[snake.size() - 1].y)) { //������ �浹
        return true;
    } 


    else { // snake move logic - �ڼ��� ������ struct.txt ����
        static int tempExitY = 0, tempExitX = 0;        // ������ gate���� ���Դ��� Ȯ���ϱ� ���� ������ �ӽ� ���� static�� �ʼ��� �־�� �Ѵ�.
        if (map.mapList[stage][headNextY][headNextX] == GATE) { // Gate �� �� ���
            score.addGate();    // gate�� �� Ƚ�� +1
            if (headNextY == Gate1.getY() && headNextX == Gate1.getX()) // Gate1�� �� ���
            {
                tempExitY = Gate2.getExitY();   // ������ gate���� ���Դ��� Ȯ���� ������ �� ���� ����
                tempExitX = Gate2.getExitX();
                headNextY = tempExitY;      // ���� �Ӹ��� ����� ����Ʈ���� ���;� �� �������� ����
                headNextX = tempExitX;
            }
            else
            {
                tempExitY = Gate1.getExitY();// Gate2�� �� ���
                tempExitX = Gate1.getExitX();
                headNextY = tempExitY;
                headNextX = tempExitX;
            }
        }
        int PrevX = snake[0].x;
        int PrevY = snake[0].y;
        int tempPrevX;
        int tempPrevY;
        snake[0].x = headNextX;
        snake[0].y = headNextY;
        if (snake[snake.size() - 1].y == tempExitY && snake[snake.size() - 1].x == tempExitX)   // ������ �����ߴ� �ӽ� ������ ��ġ�� �� ���
        {
            map.mapList[stage][Gate1.getY()][Gate1.getX()] = '1';   // gate�� �ִ� ��ġ�� ��� 1�� ��ü
            map.mapList[stage][Gate2.getY()][Gate2.getX()] = '1';
            Gate1.delGates(stage, map);     // gate ����
            map.setGate(stage);             // gate �缳��
            tempExitY = 0;      // �ӽ� ���� �ʱ�ȭ
            tempExitX = 0;
        }
        map.setMap(stage, snake[snake.size() - 1].x, snake[snake.size() - 1].y);
        for (unsigned int i = 1; i < snake.size(); i++)
        {
            tempPrevX = snake[i].x;
            tempPrevY = snake[i].y;
            snake[i].x = PrevX;
            snake[i].y = PrevY;
            PrevX = tempPrevX;
            PrevY = tempPrevY;
        }

        if (checkIncItem) { // '5'�����۰� �浹 �� ���� �߰�
            snake.push_back(SnakePart(PrevX, PrevY));
            checkIncItem = false;
            score.addSnakeLength(); // score�� snake_length +1
            if (Gate1.getY() == 0 && Gate1.getX() == 0)
            {
                map.setGate(stage);
            }
        }

        else if (checkDecItem) {//'6'�����۰� �浹 �� ���� �߰�
            SnakePart lastTail = snake.back();
            map.setMap(stage, lastTail.x,lastTail.y);
            snake.pop_back();
            checkDecItem = false;
            score.subSnakeLength(); // score�� snake_length -1
            if (score.getDecItem() == 2)    // ���࿡ dec item 2���� �Ծ����� ���� ����
            {
                return true;
            }
        }
    }
    return false;
}